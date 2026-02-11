matrixmult(float leftmatrix[], int nlrow, int nlcol,
           float rightmatrix[], int nrrow, int nrcol, float result[])
{
    float *curr_row;
    int k,l,j,ncols,nrows;
    float sum;

    nrows = nlrow;
    ncols = nrcol;
    if (nlcol == nrrow) {
        for (k = 0; k < nrows; k++) {
            curr_row = &(leftmatrix[k*nlcol]);
            for (l = 0; l < ncols; l++) {
                sum = 0.0;
                for (j = 0; j < nlcol; j++) {
                    sum = sum + curr_row[j] * rightmatrix[j*nrcol+l];
                }
                result[k*ncols+l] = sum;
            }
        }
    }
}
