covariance_sort(cpl_matrix *covar, cxint ma, cxint ia[], cxint mfit)
{

    register cxint i, j, k;
    register cxdouble swap;

    cxdouble *pd_covar = NULL;
    cxint     nr_covar;

    pd_covar = cpl_matrix_get_data(covar);
    nr_covar = cpl_matrix_get_nrow(covar);

    for (i = mfit; i < ma; i++)
        for (j = 0; j <= i; j++)
            pd_covar[i * nr_covar + j] = pd_covar[j * nr_covar + i] = 0.0;

    k = mfit - 1;
    for (j = (ma-1); j >= 0; j--) {
        if (ia[j]) {
            for (i = 0; i < ma; i++)
                SWAP(pd_covar[i * nr_covar + k],pd_covar[i * nr_covar + j])

            for (i = 0;i < ma; i++)
                SWAP(pd_covar[k * nr_covar + i],pd_covar[j * nr_covar + i])

            k--;
        }
    }

}
