#include <stdio.h>
#include <stdlib.h>

#define LEN 26

FILE *fp1, *fp2;
int n = 4;

void encode()
{
    char c;
    c = getc(fp1);
    while (c!=EOF) {
        if (c >= 'A' && c <= 'Z') {
            c = c + (n % LEN);
            if (c > 'Z') {c = 'A' + (c - 'Z') - 1;}
            fputc(c, fp2);
            goto loop1;
        }
        if (c >= 'a' && c <= 'z') {
            c = c + (n % LEN);
            if (c > 'z') {c = 'a' + (c - 'z') - 1;}
            fputc(c, fp2);
            goto loop1;
        }
        fputc(c, fp2);
        loop1:
        c = getc(fp1);
    }
    fclose(fp1);
    fclose(fp2);
}

void decode()
{
    char c;
    c = getc(fp1);
    while (c!=EOF) {
        if (c >= 'A' && c <= 'Z') {
            c = c - (n % LEN);
            if (c < 'A') {c = 'Z' - ('A' - c) + 1;}
            fputc(c, fp2);
            goto loop2;
        }
        if (c >= 'a' && c <= 'z') {
            c = c - (n % LEN);
            if (c < 'a') {c = 'z' - ('a' - c) + 1;}
            fputc(c, fp2);
            goto loop2;
        }
        fputc(c, fp2);
        loop2:
        c = getc(fp1);
    }
    fclose(fp1);
    fclose(fp2);
}

int main(int argc, char *argv[])
{
    for (int i = 1; i<5; i++) {printf("%s ", argv[i]);}

    if (argc < 4){
        printf("More information is needed.");
        return 1;
    }

    fp1 = fopen(argv[3], "r");
    fp2 = fopen(argv[4], "w");
    if (fp1 == NULL) {
        printf("Error open of input file");
        return 1;
    }
    if (fp2 == NULL) {
        printf("Error open of output file");
        return 1;
    }


    n = atoi(argv[2]);

    if (!strcmp("-decode", argv[1])) {decode(); printf("\n DECODE");}
    if (!strcmp("-encode", argv[1])) {encode(); printf("\n ENCODE");}


    return 0;
}
