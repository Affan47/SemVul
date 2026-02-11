kmo_cut_endings(cpl_vector** vec, int *begin, int *end, int cut)
{
    cpl_error_code  ret_error   = CPL_ERROR_NONE;

    int             min         = 0,
                    max         = 0,
                    i           = 0;

    double          *pvec       = NULL;

    cpl_vector      *tmp_vec    = NULL;

    KMO_TRY
    {
        KMO_TRY_ASSURE((vec != NULL) && (*vec != NULL),
                       CPL_ERROR_NULL_INPUT,
                       "Not all input data is provided!");

        KMO_TRY_EXIT_IF_NULL(
            pvec = cpl_vector_get_data(*vec));

        min = 0;
        max = cpl_vector_get_size(*vec)-1;


        for (i = 0; i < cpl_vector_get_size(*vec); i++) {
            if (pvec[i] == -1) {
                min = i+1;
            } else {
                break;
            }
        }

        if (min != cpl_vector_get_size(*vec)) {

            for (i = cpl_vector_get_size(*vec)-1; i >= 0; i--) {
                if (pvec[i] == -1) {
                    max = i-1;
                } else {
                    break;
                }
            }

            if (cut == TRUE) {

                KMO_TRY_EXIT_IF_NULL(
                    tmp_vec = cpl_vector_extract(*vec, min, max, 1));

                cpl_vector_delete(*vec); *vec= NULL;

                *vec = tmp_vec;
            }
        } else {
            if (cut == TRUE) {

                cpl_vector_delete(*vec); *vec = NULL;
            }

            min = 0;
            max = 0;
        }


        if (begin != NULL) {
            *begin = min;
        }

        if (end != NULL) {
            *end = max;
        }
    }
    KMO_CATCH
    {
        KMO_CATCH_MSG();
        ret_error = cpl_error_get_code();

        if (begin != NULL) {
            *begin = 0;
        }

        if (end != NULL) {
            *end = 0;
        }

        cpl_vector_delete(*vec); *vec= NULL;
    }

    return ret_error;
}
