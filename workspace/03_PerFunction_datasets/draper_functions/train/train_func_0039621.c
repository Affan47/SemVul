tiffsep_prn_open(gx_device * pdev)
{
    gx_device_printer * const ppdev = (gx_device_printer *)pdev;
    tiffsep_device *pdev_sep = (tiffsep_device *) pdev;
    int code, k;
    bool force_pdf, limit_icc, force_ps;
    cmm_dev_profile_t *profile_struct;


    tiff_set_handlers();


#if LIMIT_TO_ICC
    limit_icc = true;
#else
    limit_icc = false;
#endif
    code = dev_proc(pdev, get_profile)((gx_device *)pdev, &profile_struct);
    if (profile_struct->spotnames == NULL) {
        force_pdf = false;
        force_ps = false;
    } else {
        if (limit_icc) {
            force_pdf = true;
            force_ps = false;
        } else {
            force_pdf = false;
            force_ps = true;
        }
    }


    pdev_sep->warning_given = false;
    if ((pdev_sep->devn_params.page_spot_colors >= 0 || force_pdf) && !force_ps) {
        if (force_pdf) {


            pdev->color_info.num_components =
                (pdev_sep->devn_params.separations.num_separations
                 + pdev_sep->devn_params.num_std_colorant_names);
            if (pdev->color_info.num_components > pdev->color_info.max_components)
                pdev->color_info.num_components = pdev->color_info.max_components;

            pdev->color_info.max_components = pdev->color_info.num_components;
        } else {
            pdev->color_info.num_components =
                (pdev_sep->devn_params.page_spot_colors
                                     + pdev_sep->devn_params.num_std_colorant_names);
            if (pdev->color_info.num_components > pdev->color_info.max_components)
                pdev->color_info.num_components = pdev->color_info.max_components;
        }
    } else {


        int num_comp = pdev_sep->max_spots + 4;
        if (num_comp > GS_CLIENT_COLOR_MAX_COMPONENTS)
            num_comp = GS_CLIENT_COLOR_MAX_COMPONENTS;
        pdev->color_info.num_components = num_comp;
        pdev->color_info.max_components = num_comp;
    }

    if (pdev_sep->devn_params.num_separation_order_names == 0)
        for (k = 0; k < GS_CLIENT_COLOR_MAX_COMPONENTS; k++) {
            pdev_sep->devn_params.separation_order_map[k] = k;
        }
    pdev->color_info.depth = pdev->color_info.num_components *
                             pdev_sep->devn_params.bitspercomponent;
    pdev->color_info.separable_and_linear = GX_CINFO_SEP_LIN;
    code = gdev_prn_open_planar(pdev, true);
    ppdev->file = NULL;
    pdev->icc_struct->supports_devn = true;
    return code;
}
