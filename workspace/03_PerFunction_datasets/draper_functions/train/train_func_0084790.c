matrix(int nrow, int ncol) {
    double ** matrix = (double **) cpl_malloc((size_t)((nrow)*sizeof(double*)));

    int i = 0;
    for(i=0;i<nrow;i++) {
        matrix[i] = (double *) cpl_malloc((size_t)((ncol)*sizeof(double)));
    }

    return matrix;
}
