cpl_matrix_get_median(const cpl_matrix *matrix)
{
    double   median = 0.0;


    if (matrix == NULL) {
        (void)cpl_error_set_(CPL_ERROR_NULL_INPUT);
    } else {
        const cpl_size size = matrix->nr * matrix->nc;
        double  *copybuf = (double*)cpl_malloc((size_t)size * sizeof(*copybuf));

        (void)memcpy(copybuf, matrix->m, (size_t)size * sizeof(double));
        median = cpl_tools_get_median_double(copybuf, size);
        cpl_free(copybuf);
    }

    return median;
}
