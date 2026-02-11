kmo_calc_stats_vec(kmclipm_vector *data,
                                   kmclipm_vector *mask,
                                   double cpos_rej,
                                   double cneg_rej,
                                   int citer)
{
    kmclipm_vector  *data_out           = NULL;
    int             nr_non_masked_pix   = 0,
                    rejected            = 0;
    double          val                 = 0.;
    int             i                   = 0;

    KMO_TRY
    {
        KMO_TRY_ASSURE(data != NULL,
                       CPL_ERROR_NULL_INPUT,
                       "No input data is provided!");

        if (mask != NULL) {
            KMO_TRY_ASSURE(kmclipm_vector_get_size(data) ==
                           kmclipm_vector_get_size(mask),
                           CPL_ERROR_ILLEGAL_INPUT,
                           "Data and mask haven't the same size!");
        }

        KMO_TRY_ASSURE((cpos_rej >= 0.0) && (cneg_rej >= 0.0),
                       CPL_ERROR_ILLEGAL_INPUT,
                       "No negative thresholds!");

        KMO_TRY_ASSURE(citer >= 0,
                       CPL_ERROR_ILLEGAL_INPUT,
                       "No negative iterations!");


        KMO_TRY_EXIT_IF_NULL(
            data_out = kmclipm_vector_new(11));

        KMO_TRY_EXIT_IF_ERROR(
            kmclipm_vector_fill(data_out, -1.0));


        if (mask == NULL) {
            KMO_TRY_EXIT_IF_ERROR(
                kmclipm_vector_set(data_out, 0, kmclipm_vector_get_size(data)));
        } else {
            for (i = 0; i < kmclipm_vector_get_size(data); i++) {
                val = kmclipm_vector_get(mask, i, &rejected);
                if (!rejected && (val > 0.5)) {
                    nr_non_masked_pix++;
                }
            }

            KMO_TRY_EXIT_IF_ERROR(
                kmclipm_vector_set(data_out, 0, nr_non_masked_pix));


            KMO_TRY_EXIT_IF_ERROR(
                kmclipm_vector_adapt_rejected(data, mask));
        }


        if (mask == NULL) {
            KMO_TRY_EXIT_IF_ERROR(
                kmclipm_vector_set(data_out, 1,
                                   kmclipm_vector_count_non_rejected(data)));
        } else {
            nr_non_masked_pix = 0;
            for (i = 0; i < kmclipm_vector_get_size(data); i++) {
                val = kmclipm_vector_get(mask, i, &rejected);
                if (!rejected) {
                    if (val > 0.5) {
                        nr_non_masked_pix++;
                    } else {
                        kmclipm_vector_reject(data, i);
                    }
                }
            }
            KMO_TRY_EXIT_IF_ERROR(
                kmclipm_vector_set(data_out, 1, nr_non_masked_pix));
        }

        int nr_finite = kmclipm_vector_get(data_out, 1, &rejected);

        KMO_TRY_EXIT_IF_ERROR(
            kmo_calc_remaining(data,
                               data_out,
                               cpos_rej,
                               cneg_rej,
                               citer,
                               nr_finite));
    }
    KMO_CATCH
    {
        KMO_CATCH_MSG();
        kmclipm_vector_delete(data_out); data_out = NULL;
    }

    return data_out;
}
