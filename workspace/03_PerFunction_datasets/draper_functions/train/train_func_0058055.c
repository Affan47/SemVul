make_sym(DI_MUT_MATR &hits)
{
    int i,j;
    for (i=AP_A;i<AP_MAX;i*=2){
        for (j=AP_A;j<=i;j*=2){
            hits[i][j] = hits[j][i] = hits[i][j] + hits[j][i];
        }
    }
}
