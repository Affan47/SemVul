kmo_priv_is_below_threshold(double threshold,
                                cpl_vector *spec_data_out,
                                int index)
{
    double  val     = 0.0;
    int ret_val = 0;

    KMO_TRY
    {

        KMO_TRY_ASSURE(spec_data_out != NULL,
                       CPL_ERROR_NULL_INPUT,
                       "Not all input data is provided!");

        KMO_TRY_ASSURE((index >= 0) &&
                       (index < cpl_vector_get_size(spec_data_out)),
                       CPL_ERROR_NULL_INPUT,
                       "Index < 0 or larger than vector!");

        val = cpl_vector_get(spec_data_out, index);
        KMO_TRY_CHECK_ERROR_STATE();

        if (threshold > val) {
            ret_val = 1;
        }
    }
    KMO_CATCH
    {
        KMO_CATCH_MSG();
        ret_val = 0;
    }
    return ret_val;
}
