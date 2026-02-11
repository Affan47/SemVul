cpl_matrix_is_zero(const cpl_matrix *matrix, double tolerance)
{


    cpl_size     size;
    double      *m;


    if (matrix == NULL) {
        cpl_error_set_(CPL_ERROR_NULL_INPUT);
        return -1;
    }


    size = matrix->nr * matrix->nc;
    m = matrix->m;

    if (tolerance < 0.0)
        tolerance = DBL_EPSILON;

    while (size--) {
        if (!dtiny(*m, tolerance))
            return 0;
        m++;
    }

    return 1;

}
