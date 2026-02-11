cpl_stats_new_from_image(const cpl_image * image,
                                     cpl_stats_mode    mode)
{
    cpl_stats * self;

    cpl_ensure(image != NULL, CPL_ERROR_NULL_INPUT, NULL);
    self = cpl_stats_new_from_image_window(image, mode, 1, 1, image->nx,
                                           image->ny);


    if (self == NULL) (void)cpl_error_set_where_();

    return self;
}
