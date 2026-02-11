kmo_vector_get_maxpos_old(const cpl_vector *vec, int *x)
{
    int             j       = 0;

    const double    *pvec   = NULL;

    double          val     = 0.0;

    cpl_error_code  ret_error   = CPL_ERROR_NONE;

    KMO_TRY
    {
        KMO_TRY_ASSURE(vec != NULL,
                       CPL_ERROR_NULL_INPUT,
                       "No input data is provided!");

        KMO_TRY_EXIT_IF_NULL(
            pvec = cpl_vector_get_data_const(vec));

        for (j = 0; j < cpl_vector_get_size(vec); j++) {
            if (val < pvec[j]) {
                val = pvec[j];
                *x = j;
            }
        }
    }
    KMO_CATCH
    {
        KMO_CATCH_MSG();
        ret_error = cpl_error_get_code();
    }

    return ret_error;
}
