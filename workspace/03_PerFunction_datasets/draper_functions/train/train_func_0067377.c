kmclipm_vector_multiply(kmclipm_vector *kv1, const kmclipm_vector *kv2)
{
    int             i           = 0,
                    size        = 0;
    double          *pkv1data   = NULL,
                    *pkv1mask   = NULL,
                    *pkv2data   = NULL,
                    *pkv2mask   = NULL;
    cpl_error_code  err         = CPL_ERROR_NONE;

    KMCLIPM_TRY
    {
        KMCLIPM_TRY_CHECK_AUTOMSG((kv1 != NULL) && (kv2 != NULL),
                                  CPL_ERROR_NULL_INPUT);

        size = cpl_vector_get_size(kv1->data);
        KMCLIPM_TRY_CHECK_ERROR_STATE();

        KMCLIPM_TRY_CHECK_AUTOMSG(size == cpl_vector_get_size(kv2->data),
                       CPL_ERROR_ILLEGAL_INPUT);

        KMCLIPM_TRY_EXIT_IFN(
            pkv1data = cpl_vector_get_data(kv1->data));
        KMCLIPM_TRY_EXIT_IFN(
            pkv1mask = cpl_vector_get_data(kv1->mask));
        KMCLIPM_TRY_EXIT_IFN(
            pkv2data = cpl_vector_get_data(kv2->data));
        KMCLIPM_TRY_EXIT_IFN(
            pkv2mask = cpl_vector_get_data(kv2->mask));

        for (i = 0; i < size; i++) {
            if ((pkv1mask[i] > 0.5) && (pkv2mask[i] > 0.5)) {


                pkv1data[i] *= pkv2data[i];

                if (kmclipm_is_nan_or_inf(pkv1data[i])) {

                    pkv1mask[i] = 0.;
                }
            } else {

                pkv1mask[i] = 0.;
            }
        }
    }
    KMCLIPM_CATCH
    {
        err = cpl_error_get_code();
    }

    return err;
}
