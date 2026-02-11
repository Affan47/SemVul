cpl_matrix_subtract_scalar(cpl_matrix *matrix, double value)
{


    cpl_size     size;
    double      *m;


    if (matrix == NULL)
        return cpl_error_set_(CPL_ERROR_NULL_INPUT);

    size = matrix->nr * matrix->nc;
    m = matrix->m;

    cpl_tools_add_flops( (cpl_flops)size );
    while (size--)
        *m++ -= value;

    return CPL_ERROR_NONE;

}
