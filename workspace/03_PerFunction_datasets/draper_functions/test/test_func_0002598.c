cpl_matrix_extract_diagonal(const cpl_matrix *matrix, cpl_size diagonal)
{


    cpl_matrix  *output;
    cpl_size          diagonal_count;
    cpl_size          diagonal_length;
    cpl_size          i, r, c;
    double      *m;
    double      *om;


    if (matrix == NULL) {
        cpl_error_set_(CPL_ERROR_NULL_INPUT);
        return NULL;
    }

    diagonal_count = labs(matrix->nr - matrix->nc) + 1;

    if (diagonal < 0 || diagonal >= diagonal_count) {
        cpl_error_set_(CPL_ERROR_ACCESS_OUT_OF_RANGE);
        return NULL;
    }

    diagonal_length = matrix->nr < matrix->nc ? matrix->nr : matrix->nc;

    output = (cpl_matrix *)cpl_malloc(sizeof(cpl_matrix));
    om = output->m = (double *)cpl_malloc((size_t)diagonal_length
                                          * sizeof(*om));

    if (matrix->nc < matrix->nr) {
        r = diagonal;
        c = 0;
        output->nr = 1;
        output->nc = diagonal_length;
    }
    else {
        r = 0;
        c = diagonal;
        output->nr = diagonal_length;
        output->nc = 1;
    }

    m = matrix->m + c + r * matrix->nc;
    for (i = 0; i < diagonal_length; i++, m += matrix->nc + 1)
        *om++ = *m;

    return output;

}
