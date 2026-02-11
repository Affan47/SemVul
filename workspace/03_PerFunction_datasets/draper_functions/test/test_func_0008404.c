kmo_idl_values_at_indices(const cpl_vector *data,
                                      const cpl_vector *indices)
{
    cpl_vector*     ret_vec     = NULL;

    double          *pret_vec   = NULL;

    const double    *pdata      = NULL,
                    *pindices   = NULL;

    int             i           = 0,
                    size        = 0;

    KMO_TRY
    {
        KMO_TRY_ASSURE((data != NULL) &&
                       (indices != NULL),
                       CPL_ERROR_NULL_INPUT,
                       "Not all input data is provided!");

        KMO_TRY_EXIT_IF_NULL(
            pdata = cpl_vector_get_data_const(data));

        KMO_TRY_EXIT_IF_NULL(
            pindices = cpl_vector_get_data_const(indices));

        size = cpl_vector_get_size(indices);

        KMO_TRY_EXIT_IF_NULL(
            ret_vec = cpl_vector_new(size));

        KMO_TRY_EXIT_IF_NULL(
            pret_vec = cpl_vector_get_data(ret_vec));

        for (i = 0; i < size; i++) {
            if ((int)pindices[i] < 0) {
                KMO_TRY_ERROR_SET_MSG(CPL_ERROR_ILLEGAL_INPUT,
                                      "One of the indices is < 0!");
            } else {
                pret_vec[i] = pdata[(int)pindices[i]];
            }
        }
    }
    KMO_CATCH
    {
        KMO_CATCH_MSG();
        cpl_vector_delete(ret_vec); ret_vec = NULL;
    }

    return ret_vec;
}
