kmo_image_fill(cpl_image *img, double value)
{
    float          *pimg       = NULL;

    int             i           = 0;

    cpl_error_code  ret_error   = CPL_ERROR_NONE;

    KMO_TRY
    {
        KMO_TRY_ASSURE(img != NULL,
                       CPL_ERROR_NULL_INPUT,
                       "Not all input data is provided!");

        KMO_TRY_EXIT_IF_NULL(
            pimg = cpl_image_get_data_float(img));

        for (i = 0;
             i < cpl_image_get_size_x(img) * cpl_image_get_size_y(img);
             i++) {
            pimg[i] = value;
        }
    }
    KMO_CATCH
    {
        KMO_CATCH_MSG();
        ret_error = cpl_error_get_code();
    }

    return ret_error;
}
