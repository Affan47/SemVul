kmo_create_line_profile(const cpl_image* data,
                                        int lo,
                                        int hi)
{
    kmclipm_vector  *profile    = NULL,
                    *tmp_vec    = NULL;
    const float     *pdata      = NULL;
    int             nx          = 0,
                    i           = 0,
                    j           = 0,
                    k           = 0;

    KMO_TRY
    {
        KMO_TRY_ASSURE(data != NULL,
                       CPL_ERROR_NULL_INPUT,
                       "Not all input data is provided!");

        KMO_TRY_ASSURE(lo <= hi,
                       CPL_ERROR_ILLEGAL_INPUT,
                       "lo must be smaller than hi!");

        nx = cpl_image_get_size_x(data);

        KMO_TRY_EXIT_IF_NULL(
            pdata = cpl_image_get_data_float_const(data));

        KMO_TRY_EXIT_IF_NULL(
            profile = kmclipm_vector_new(nx));

        KMO_TRY_EXIT_IF_NULL(
            tmp_vec = kmclipm_vector_new(hi - lo + 1));

        for (i = 0; i < nx; i++) {
            k = 0;
            for (j = lo; j <= hi; j++) {
                kmclipm_vector_set(tmp_vec, k++, pdata[i+j*nx]);
            }

            if ((i < KMOS_BADPIX_BORDER) || (i >= nx-KMOS_BADPIX_BORDER)) {

                kmclipm_vector_set(profile, i, 0);
                kmclipm_vector_reject(profile, i);
            } else {
                kmclipm_vector_set(profile, i,
                                   kmclipm_vector_get_median(tmp_vec, KMCLIPM_ARITHMETIC));
            }
            KMO_TRY_CHECK_ERROR_STATE();
        }
    }
    KMO_CATCH
    {
        KMO_CATCH_MSG();
        kmclipm_vector_delete(profile); profile = NULL;
    }

    kmclipm_vector_delete(tmp_vec); tmp_vec = NULL;

    return profile;
}
