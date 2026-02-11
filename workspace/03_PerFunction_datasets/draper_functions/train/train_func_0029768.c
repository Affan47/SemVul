cpl_matrix_get_determinant(const cpl_matrix *matrix)
{

    cpl_matrix   * self;
    cpl_array    * perm;
    int          * iperm;
    double         determinant;
    int            sig;
    cpl_errorstate prevstate = cpl_errorstate_get();
    cpl_error_code error;


    cpl_ensure(matrix != NULL,           CPL_ERROR_NULL_INPUT,    0.0);
    cpl_ensure(matrix->nr == matrix->nc, CPL_ERROR_ILLEGAL_INPUT, 0.0);

    iperm = (int*) cpl_malloc((size_t)matrix->nr * sizeof(*iperm));

    perm = cpl_array_wrap_int(iperm, matrix->nr);

    self = cpl_matrix_duplicate(matrix);

    error = cpl_matrix_decomp_lu(self, perm, &sig);

    cpl_array_delete(perm);

    if (!error) {
        cpl_size i;

        cpl_long_double ldet = (cpl_long_double)sig;
        for (i = 0; i < matrix->nr; i++) {
            const double aii = cpl_matrix_get(self, i, i);

            ldet *= (cpl_long_double)aii;

            if (ldet == 0.0) break;

        }

        determinant = (double)ldet;

        if (i < matrix->nr) {
            (void)cpl_error_set_message_(CPL_ERROR_UNSPECIFIED,
                                         "Underflow at pivot %" CPL_SIZE_FORMAT
                                         " of %" CPL_SIZE_FORMAT,
                                         1+i, matrix->nr);
        } else if (determinant == 0.0) {
            (void)cpl_error_set_message_(CPL_ERROR_UNSPECIFIED,
                                         "Underflow at %Lg", ldet);
        }

    } else {

        determinant = 0.0;

        if (error == CPL_ERROR_SINGULAR_MATRIX) {
            cpl_errorstate_set(prevstate);
        } else {

            (void)cpl_error_set_where_();
        }
    }

    cpl_matrix_delete(self);

    return determinant;

}
