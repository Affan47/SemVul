rate_write(DI_MUT_MATR &hits,FILE *out){
    int i,j;
    for (i=AP_A;i<AP_MAX;i*=2){
        for (j=AP_A;j<AP_MAX;j*=2){
            fprintf(out,"%5li ",hits[i][j]);
        }
        fprintf(out,"\n");
    }
}
