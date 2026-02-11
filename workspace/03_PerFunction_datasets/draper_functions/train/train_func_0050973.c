cpl_matrix_product_normal(cpl_matrix * self,
                                         const cpl_matrix * other)
{

    double         sum;
    const double * ai = cpl_matrix_get_data_const(other);
    const double * aj;
    double       * bwrite = cpl_matrix_get_data(self);
    const cpl_size m = cpl_matrix_get_nrow(self);
    const cpl_size n = cpl_matrix_get_ncol(other);
    cpl_size       i, j, k;


    cpl_ensure_code(self  != NULL, CPL_ERROR_NULL_INPUT);
    cpl_ensure_code(other != NULL, CPL_ERROR_NULL_INPUT);
    cpl_ensure_code(cpl_matrix_get_ncol(self)  == m, CPL_ERROR_ILLEGAL_INPUT);
    cpl_ensure_code(cpl_matrix_get_nrow(other) == m,
                    CPL_ERROR_INCOMPATIBLE_INPUT);

#ifdef CPL_MATRIX_PRODUCT_NORMAL_RESET


    (void)memset(bwrite, 0, m * n * sizeof(*bwrite));
#endif


    for (i = 0; i < m; i++, bwrite += m, ai += n) {
        aj = ai;
        for (j = i; j < m; j++, aj += n) {
            sum = 0.0;
            for (k = 0; k < n; k++) {
                sum += ai[k] * aj[k];
            }
            bwrite[j] = sum;
        }
    }

    cpl_tools_add_flops((cpl_flops)(n * m * (m + 1)));

    return CPL_ERROR_NONE;
}
