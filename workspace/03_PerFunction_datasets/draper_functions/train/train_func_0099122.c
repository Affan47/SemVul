kmo_vector_divide(cpl_vector *vec1, cpl_vector *vec2)
{
    double          *dd1        = NULL,
                    *dd2        = NULL;
    int             size        = 0,
                    i           = 0;
    cpl_error_code  ret_error   = CPL_ERROR_NONE;

    KMO_TRY
    {
        KMO_TRY_ASSURE((vec1 != NULL) && (vec2 != NULL),
                       CPL_ERROR_NULL_INPUT,
                       "Not all input data is provided!");

        size = cpl_vector_get_size(vec1);
        KMO_TRY_CHECK_ERROR_STATE();

        KMO_TRY_ASSURE(size == cpl_vector_get_size(vec2),
                       CPL_ERROR_ILLEGAL_INPUT,
                       "First and second vector don't have the same size!");

        KMO_TRY_EXIT_IF_NULL(
            dd1 = cpl_vector_get_data(vec1));
        KMO_TRY_EXIT_IF_NULL(
            dd2 = cpl_vector_get_data(vec2));

        for (i = 0; i < size; i++) {
            dd1[i] /= dd2[i];
        }
    }
    KMO_CATCH
    {
        KMO_CATCH_MSG();
        ret_error = cpl_error_get_code();
    }

    return ret_error;
}
