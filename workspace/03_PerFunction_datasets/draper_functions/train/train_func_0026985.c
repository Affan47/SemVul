kmclipm_setup_grid_band_lcal(gridDefinition *gd,
                                            const cpl_image *lcal,
                                            const char *filter_id,
                                            int bandwidth_method,
                                            const cpl_table *tbl)
{
    cpl_error_code  ret_error   = CPL_ERROR_NONE;
    double          tol         = 0.001;
    float           tmp_start   = 0,
                    tmp_end     = 0;
    const float     *ptbl       = NULL;

    KMCLIPM_TRY
    {

        KMCLIPM_TRY_CHECK((gd != NULL) &&
                          (tbl != NULL),
                          CPL_ERROR_NULL_INPUT,
                          NULL,
                          "Not all input data is provided!");

        KMCLIPM_TRY_EXIT_IFN(
            ptbl = cpl_table_get_data_float_const(tbl, filter_id));

        if (bandwidth_method == 0) {

            if (fabs(kmclipm_band_start + 1.0) < tol) {

                tmp_start = ptbl[0];
            } else {

                tmp_start = kmclipm_band_start;
            }


            if (fabs(kmclipm_band_end + 1.0) < tol) {

                tmp_end = ptbl[1];
            } else {

                tmp_end = kmclipm_band_end;
            }


            gd->l.start = tmp_start;
            gd->l.delta = (tmp_end - tmp_start) / kmclipm_band_samples;
        }
        else if (bandwidth_method == 1) {
            KMCLIPM_TRY_CHECK(lcal != NULL,
                              CPL_ERROR_NULL_INPUT,
                              NULL,
                              "Not all input data is provided!");


            if (fabs(kmclipm_band_start + 1.0) < tol) {

                tmp_start = cpl_image_get_min(lcal);
            } else {

                tmp_start = kmclipm_band_start;
            }


            if (fabs(kmclipm_band_end + 1.0) < tol) {

                tmp_end = cpl_image_get_max(lcal);
            } else {

                tmp_end = kmclipm_band_end;
            }


            gd->l.dim = KMOS_DETECTOR_SIZE;
            gd->l.delta = (tmp_end - tmp_start) / (gd->l.dim - 2*KMOS_BADPIX_BORDER);
            gd->l.start = tmp_start - KMOS_BADPIX_BORDER*gd->l.delta;
        }


        cpl_msg_info("",
                     "Resampled wavelength range for this detector: "
                     "%5.4g-%5.4gum with %d samples",
                     gd->l.start,
                     gd->l.start + gd->l.dim * gd->l.delta,
                     gd->l.dim);
    }
    KMCLIPM_CATCH
    {
        ret_error = cpl_error_get_code();
    }

    return ret_error;
}
