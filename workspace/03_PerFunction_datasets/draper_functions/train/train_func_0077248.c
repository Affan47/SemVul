cpl_image_get_maxpos_window(const cpl_image * image,
                                           cpl_size          llx,
                                           cpl_size          lly,
                                           cpl_size          urx,
                                           cpl_size          ury,
                                           cpl_size        * px,
                                           cpl_size        * py)
{
    cpl_stats * stats;

    cpl_ensure_code(px != NULL, CPL_ERROR_NULL_INPUT);
    cpl_ensure_code(py != NULL, CPL_ERROR_NULL_INPUT);

    stats = cpl_stats_new_from_image_window(image, CPL_STATS_MAXPOS,
                                            llx, lly,  urx, ury);

    cpl_ensure_code(stats != NULL, cpl_error_get_code());


    *px = cpl_stats_get_max_x(stats);
    *py = cpl_stats_get_max_y(stats);

    cpl_stats_delete(stats);

    return CPL_ERROR_NONE;
}
