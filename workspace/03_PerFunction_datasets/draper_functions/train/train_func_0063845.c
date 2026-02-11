kmclipm_vector_power(kmclipm_vector *kv, double exponent)
{
    int             i           = 0,
                    n           = 0;
    double          *pkvmask    = NULL,
                    *pkvdata    = NULL;
    cpl_error_code  err         = CPL_ERROR_NONE;

    KMCLIPM_TRY
    {
        KMCLIPM_TRY_CHECK_AUTOMSG(kv != NULL,
                                  CPL_ERROR_NULL_INPUT);

        if (exponent == 0.0) {

            kmclipm_vector_multiply_scalar(kv, 0.0);
            KMCLIPM_TRY_CHECK_ERROR_STATE();

            kmclipm_vector_add_scalar(kv, 1.0);
            KMCLIPM_TRY_CHECK_ERROR_STATE();
        } else {
            n = cpl_vector_get_size(kv->data);
            KMCLIPM_TRY_CHECK_ERROR_STATE();

            KMCLIPM_TRY_EXIT_IFN(
                pkvdata = cpl_vector_get_data(kv->data));
            KMCLIPM_TRY_EXIT_IFN(
                pkvmask = cpl_vector_get_data(kv->mask));
            for (i = 0; i < n; i++) {
                if (pkvmask[i] > 0.5) {
                    pkvdata[i] = pow(pkvdata[i], exponent);
                }
                if (kmclipm_is_nan_or_inf(pkvdata[i])) {

                    pkvmask[i] = 0.;
                }
            }
        }
    }
    KMCLIPM_CATCH
    {
        err = cpl_error_get_code();
    }

    return err;
}
