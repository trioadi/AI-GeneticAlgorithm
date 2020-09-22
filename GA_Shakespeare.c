#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char target[] = "trioadipamungkas";
int popmax = 300; // maksimal populasi
float mutationRate = 0.01; //rate 1%
char pop[]; //DNA
char child[];
char popall[3001][18]; //jumlah populasi | banyaknya DNA/character
char popnew[3001][18];
char matingPool[3001][18];
float fit_norm[3008];
int midpoint;
float fit_sigma = 0.0;
int matingPool_length = 0;
int loop = 0;

void population();
void calcFitness();
void naturalSelection();
void generate();

int main(){
   midpoint = strlen(target)/2;
//    fit_norm[popmax];
    srand(time(0));
    population();
    while(true){
        calcFitness();
        naturalSelection();
        generate();
        loop++;
        printf("loop ke: %d\n", loop);
    }  
}

// create population 
void population(){
    int i;
    //Generate N member of Population
    for (i = 0; i < popmax; i++){
        int j;
        //Generate N DNA for each individu
        for (j = 0; j < strlen(target) ; j++) { 
            int num = (rand() % (122 - 65 + 1)) + 65; // random number in ASCII
                pop[j] = (char)num;
                //printf("%c", pop[i]); 
        }
    //Save DNA each individu
    strcpy(popall[i], pop);
    //printf("%s \n", popall[i]);
    }
}

void calcFitness(){
    // Pencocokan DNA semua populasi
    int fit_total = 0;
    int fitness[popmax];
    int i;
    for(i = 0; i < popmax; i++){
        int j;
        int DNA_match = 0;
        
        // Check matching char for every member of population
        for(j = 0; j < strlen(target); j++){
           
            // check for every DNA a member
            if(target[j] == popall[i][j]){
            //printf("nilai %c %c \n", target[j], popall[i][j]);
            DNA_match++;
            // Simpan indeks dengan fitness terbesar
            fit_total = fit_total + 1;
            }
        }
    //menyimpan fitness per individu
    fitness[i] = DNA_match;

    printf("%s ", popall[i]);
    printf("fitness: %d ", fitness[i]);
    printf("fitness Total: %d \n", fit_total);
    
    // Break process when fitness = length of char target
    if(strlen(target) == DNA_match){
        printf("Match with target: %s\n", target);
        printf("Total Generation: %d\n", loop);
        printf("Mutation Rate: %.0f Percent\n", 100*mutationRate);
        break;
    }

    }
    //normalize fitness per individu
    int k;
    for(k=0; k<popmax; k++){
           fit_norm[k] = (float)fitness[k]/(float)fit_total;
    //printf("fitness norm: %.5f \n", fit_norm[k]); 
    }
}

void naturalSelection(){
    int indeks_ke = 0;
    int fit_loop = 0;
    fit_sigma = 0;

    int i;
    for(i = 0; i < popmax; i++){
        int j;
        for(j = 0; j < fit_norm[i]*popmax; j++){
            strcpy(matingPool[indeks_ke], popall[i]);   
            //printf("indeks ke: %d\n", indeks_ke);
            //printf("mating pool: %s \n", matingPool[indeks_ke]);
            indeks_ke++;
        }
        fit_loop = fit_loop + fit_norm[i]*popmax;   
        fit_sigma = fit_sigma + fit_norm[i]; // total fitness normalize
        //printf("total loop: %d \n", fit_loop);
 
    }
    matingPool_length = indeks_ke;    
    //printf("total: %f\n", fit_sigma);

}  

//create next generation
void generate(){
    int parentA_int;
    int parentB_int;
    char parentA[18];
    char parentB[18];
    
    int i;
    for(i=0; i<popmax; i++){
        // Select random parent from mating pool
        parentA_int = (rand() % (matingPool_length - 0 + 1)) + 0; // range 0 to maxlength of matingpool
        strcpy(parentA, matingPool[parentA_int]); //Parent A
        parentB_int = (rand() % (matingPool_length - 0 + 1)) + 0; // range 0 to maxlength of matingpool  
        strcpy(parentB, matingPool[parentB_int]); // Parent B
        //printf("parent: %d %d \n", parentA_int, parentB_int);

        //crossover
        int j;
        for(j = 0; j < strlen(target); j++){
            if(j<midpoint) child[j] = parentA[j];
            if(j>=midpoint) child[j] = parentB[j];
        //printf("anak: %c \n", child[j]);
        }

        // mutasi DNA
        int k;
        for (k = 0; k < strlen(target); k++)
        {
            int randval = rand() % (100 + 1);
            if( mutationRate*100 > randval ){
                child[k] = (char)((rand() % (122 - 65 + 1)) + 65);
            }
        }
    strcpy(popall[i], child);    
    //printf("child: %s\n", popall[i]);
    }
}
