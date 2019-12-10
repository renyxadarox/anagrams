#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <inttypes.h>
#include <string.h>
#include <time.h>

#define MAX_ROW_SIZE 1000000
#define LETTERS_CNT 26

FILE * finput, * foutput;
const char * input_file_name = "input.txt";
const char * output_file_name = "output.txt";
char ** a;
int32_t ** letters;
uint32_t out_cnt = 0;

char ** create_char_array(int rows, int cols){
    char ** p;
    int i;
    p = (char **)malloc(sizeof(char*)*rows);
    for(i=0; i<rows; i++){
        p[i]=(char *)malloc(sizeof(char)*cols);
    }
    return p;
}

char ** erase_char_array(int rows, char ** p){
    int i;
    for(i=0; i<rows; i++){
        free(p[i]);
    }
    free(p);
    return NULL;
}

int32_t ** create_int32_t_array(int rows, int cols){
    int32_t ** p;
    int i;
    p = (int32_t **)malloc(sizeof(int32_t*)*rows);
    for(i=0; i<rows; i++){
        p[i]=(int32_t *)malloc(sizeof(int32_t)*cols);
    }
    return p;
}

char ** erase_int32_t_array(int rows, int32_t ** p){
    int i;
    for(i=0; i<rows; i++){
        free(p[i]);
    }
    free(p);
    return NULL;
}

int read_input(void)
{
    char * estr;
    int i;
    finput = fopen(input_file_name, "r");
    if(finput == NULL)
        return (EXIT_FAILURE);
    for (i=0; i<2; i++){
        estr = fgets(a[i], MAX_ROW_SIZE, finput);
        if (estr == NULL) {
            exit(EXIT_FAILURE);
        }
    }
    fclose(finput);
    return 0;
}

int write_output(void)
{
    foutput = fopen(output_file_name, "w");
    if(finput == NULL)
        return (EXIT_FAILURE);
    printf("%" PRIu32 "\n", out_cnt);
    fprintf(foutput, "%" PRIu32 "\n", out_cnt);
    fflush(foutput);
    fclose(foutput);
    return 0;
}

int main()
{
    a = create_char_array(2, MAX_ROW_SIZE);
    letters = create_int32_t_array(2, LETTERS_CNT);

    read_input();
//    printf ("I have read:\n%s%s",a[0],a[1]);

    int i, j;
    char * t;
    for (i=0; i<2; i++) {
        for (j=0; j<LETTERS_CNT; j++)
            letters[i][j] = 0;
    }
    for (i=0; i<2; i++)
        for (t = a[i]; *t != '\0'; t++)
            letters[i][(int)(*t) - (int)('A')]++;
/*
    for (i=0; i<2; i++)
        for (j=0; j<LETTERS_CNT; j++)
            printf ("%c[%i] - %d\n",(char)(j+(int)('A')),i,letters[i][j]);
*/

    for (j=0; j<LETTERS_CNT; j++) {
        out_cnt += abs(letters[0][j] - letters[1][j]);
//        printf ("%c - %d\n",(char)(j+(int)('A')),abs(letters[0][j] - letters[1][j]));
    }

    write_output();

    erase_char_array(2, a);
    erase_int32_t_array(2, letters);
    return 0;
}
