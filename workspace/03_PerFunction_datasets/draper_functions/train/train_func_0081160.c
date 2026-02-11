assignnodes(int ndim, int nfactor, int *pfacts, int *counts, int **pdims)
{
    int *bins;
    int i, j;
    int n;
    int f;
    int *p;
    int *pmin;

    if (0 >= ndim) {
       return MPI_ERR_DIMS;
    }


    bins = (int *) malloc((unsigned) ndim * sizeof(int));
    if (NULL == bins) {
       return MPI_ERR_NO_MEM;
    }
    *pdims = bins;

    for (i = 0, p = bins; i < ndim; ++i, ++p) {
        *p = 1;
     }


    for (j = nfactor - 1; j >= 0; --j) {
       f = pfacts[j];
       for (n = counts[j]; n > 0; --n) {

            pmin = bins;
            for (i = 1, p = pmin + 1; i < ndim; ++i, ++p) {
                if (*p < *pmin) {
                    pmin = p;
                }
            }
            *pmin *= f;
        }
     }


     for (i = 0, pmin = bins; i < ndim - 1; ++i, ++pmin) {
         for (j = i + 1, p = pmin + 1; j < ndim; ++j, ++p) {
             if (*p > *pmin) {
                n = *p;
                *p = *pmin;
                *pmin = n;
             }
         }
     }

     return MPI_SUCCESS;
}
