hawki_compute_flatbpm
(const cpl_image *   in,
 double              sigma,
 double              lowval,
 double              highval)
{
    cpl_mask            *   kernel ;
    cpl_image           *   filtered ;
    double                  med, stdev, threshold ;
    cpl_image           *   bpm_sigma;
    cpl_image           *   bpm_lowhigh;
    cpl_image           *   bpm;
    cpl_image           *   bpm_int ;


    if (in == NULL) return NULL ;
    if (sigma <= 0) return NULL ;


    kernel = cpl_mask_new(3, 3) ;
    cpl_mask_not(kernel) ;
    filtered = cpl_image_new(cpl_image_get_size_x(in), cpl_image_get_size_y(in),
                             cpl_image_get_type(in));
    cpl_image_filter_mask(filtered, in, kernel, CPL_FILTER_MEDIAN,
                          CPL_BORDER_FILTER);
    cpl_mask_delete(kernel) ;


    bpm_sigma = cpl_image_subtract_create(in, filtered) ;
    cpl_image_delete(filtered) ;


    med = cpl_image_get_median_dev(bpm_sigma, &stdev) ;
    threshold = med + sigma*stdev ;
    cpl_msg_info(__func__, "Threshold : %g = %g + %g * %g",
            threshold, med, sigma, stdev) ;


    cpl_image_threshold(bpm_sigma, threshold, threshold, 0.0, 1.0) ;


    bpm_lowhigh = cpl_image_duplicate(in);
    hawki_image_inverse_threshold(bpm_lowhigh, lowval, highval, 0.0, 1.0);


    bpm = cpl_image_add_create(bpm_sigma, bpm_lowhigh);
    cpl_image_threshold(bpm, 0.0, 1.0, 0.0, 1.0);


    bpm_int = cpl_image_cast(bpm, CPL_TYPE_INT) ;
    cpl_image_delete(bpm) ;
    cpl_image_delete(bpm_sigma);
    cpl_image_delete(bpm_lowhigh);

    return bpm_int ;
}
