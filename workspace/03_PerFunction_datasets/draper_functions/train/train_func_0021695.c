cpl_imagelist_threshold(
        cpl_imagelist * imlist,
        double          lo_cut,
        double          hi_cut,
        double          assign_lo_cut,
        double          assign_hi_cut)
{
    cpl_size                i;


    cpl_ensure_code(imlist != NULL, CPL_ERROR_NULL_INPUT);
    cpl_ensure_code(lo_cut < hi_cut, CPL_ERROR_INCOMPATIBLE_INPUT);

    for (i=0; i<imlist->ni; i++)
        cpl_ensure_code(!cpl_image_threshold(imlist->images[i], lo_cut, hi_cut,
                                             assign_lo_cut, assign_hi_cut),
                        cpl_error_get_code());

    return CPL_ERROR_NONE;
}
