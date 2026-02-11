mos_lssflat_normalise
(cpl_image *flat, int spa_smooth_radius, int disp_smooth_radius,
 int spa_fit_nknots, int disp_fit_nknots,
 double fit_threshold)
{
    const char     *func = "mos_normalise_longflat";

    cpl_image      *smo_flat;

    if (flat == NULL) {
        cpl_error_set(func, CPL_ERROR_NULL_INPUT);
        return NULL;
    }

    if (spa_fit_nknots < 1 && spa_smooth_radius < 1) {
        cpl_error_set(func, CPL_ERROR_ILLEGAL_INPUT);
        return NULL;
    }
    if (disp_fit_nknots < 1 && disp_smooth_radius < 1) {
        cpl_error_set(func, CPL_ERROR_ILLEGAL_INPUT);
        return NULL;
    }

    smo_flat = cpl_image_duplicate(flat);
    mosca::image smoothed_flat(smo_flat);

    if (spa_fit_nknots < 0)
    {
        mosca::image_smooth_1d_median<float>(smoothed_flat,
                                             spa_smooth_radius,
                                             mosca::SPATIAL_AXIS);
    }
    else
        mosca::image_cubicspline_1d_fit<float>(smoothed_flat, spa_fit_nknots,
                                               fit_threshold,
                                               mosca::SPATIAL_AXIS);


    if (disp_fit_nknots < 0)
    {
        mosca::image_smooth_1d_median<float>(smoothed_flat,
                                             disp_smooth_radius,
                                             mosca::DISPERSION_AXIS);
    }
    else
        mosca::image_cubicspline_1d_fit<float>(smoothed_flat, disp_fit_nknots,
                                               fit_threshold,
                                               mosca::DISPERSION_AXIS);


    cpl_image_divide(flat, smo_flat);

    return smo_flat;
}
