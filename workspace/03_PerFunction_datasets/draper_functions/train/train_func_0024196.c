hdrl_mime_linalg_solve_tikhonov(const cpl_matrix * mat,
          const cpl_matrix * rhs, double alpha)
{
    cpl_matrix *normal;
    cpl_matrix *solution;
    cpl_error_code error;


    if (mat == NULL || rhs == NULL)
    {
        cpl_error_set(cpl_func, CPL_ERROR_NULL_INPUT);
        return NULL;
    }

    if (cpl_matrix_get_nrow(mat) != cpl_matrix_get_nrow(rhs))
    {
        cpl_error_set(cpl_func, CPL_ERROR_INCOMPATIBLE_INPUT);
        return NULL;
    }


    normal = hdrl_mime_linalg_normal_equations_create(mat, alpha);
    error = cpl_matrix_decomp_chol(normal);

    if (error != CPL_ERROR_NONE)
    {
        cpl_matrix_delete(normal);
        return NULL;
    }


    solution = hdrl_mime_matrix_product_left_transpose_create(mat, rhs);
    error = cpl_matrix_solve_chol(normal, solution);
    cpl_matrix_delete(normal);

    if (error != CPL_ERROR_NONE)
    {
        cpl_matrix_delete(solution);
        return NULL;
    }

    return solution;
}
