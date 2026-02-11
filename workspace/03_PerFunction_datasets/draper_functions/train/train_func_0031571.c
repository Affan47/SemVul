kmo_calc_noise_map(cpl_image *data,
                              double gain,
                              double readnoise)
{
    cpl_image       *noise_img      = NULL;

    KMO_TRY
    {
        KMO_TRY_ASSURE(data != NULL,
                       CPL_ERROR_NULL_INPUT,
                       "Not all input data is provided!");

        KMO_TRY_ASSURE(gain >= 0.0,
                       CPL_ERROR_ILLEGAL_INPUT,
                       "No negative gain!");

        KMO_TRY_ASSURE(readnoise >= 0.0,
                       CPL_ERROR_ILLEGAL_INPUT,
                       "No negative readnoise!");


        KMO_TRY_EXIT_IF_NULL(
            noise_img = cpl_image_multiply_scalar_create(data, gain));

        KMO_TRY_EXIT_IF_ERROR(
            cpl_image_add_scalar(noise_img, readnoise * readnoise));

        if (cpl_image_get_min (noise_img) < 0.0) {
            if (print_warning_once_noise == TRUE) {
                cpl_msg_warning(cpl_func, "Negative pixels are set to zero in"
                                          " order to calculate noise map!");
                  print_warning_once_noise = FALSE;
            }
            float *pnoise_img = cpl_image_get_data_float(noise_img);
            int i = 0;
            for (i = 0;
                 i < cpl_image_get_size_x(noise_img)*cpl_image_get_size_y(noise_img);
                 i++)
            {
                if (pnoise_img[i] < 0.0) {
                    pnoise_img[i] = 0.0;
                }
            }
        }

        KMO_TRY_EXIT_IF_ERROR(
            cpl_image_power(noise_img, 0.5));

        if (gain != 0.0) {
            KMO_TRY_EXIT_IF_ERROR(
                cpl_image_divide_scalar(noise_img, gain));
        } else {
            KMO_TRY_EXIT_IF_ERROR(
                kmo_image_divide_scalar(noise_img, gain));
        }
    }
    KMO_CATCH
    {
        KMO_CATCH_MSG();
        cpl_image_delete(noise_img); noise_img = NULL;
    }

    return noise_img;
}
