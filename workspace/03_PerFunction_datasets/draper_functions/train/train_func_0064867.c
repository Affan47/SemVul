check_rgb_color_model_comps(gx_device * dev)
{
    gx_device_color_info *          pcinfo = &dev->color_info;
    int                             ncomps = pcinfo->num_components;
    int                             red_c, green_c, blue_c;
    const gx_cm_color_map_procs *   pprocs;
    cm_map_proc_rgb((*map_rgb));
    frac                            frac_14 = frac_1 / 4;
    frac                            out[GX_DEVICE_COLOR_MAX_COMPONENTS];
    gx_color_index                  process_comps;


    if ( ncomps < 3                                       ||
         (red_c = dev_proc(dev, get_color_comp_index)(
                       dev,
                       "Red",
                       sizeof("Red") - 1,
                       NO_COMP_NAME_TYPE )) < 0           ||
         red_c == GX_DEVICE_COLOR_MAX_COMPONENTS         ||
         (green_c = dev_proc(dev, get_color_comp_index)(
                          dev,
                          "Green",
                          sizeof("Green") - 1,
                          NO_COMP_NAME_TYPE )) < 0        ||
         green_c == GX_DEVICE_COLOR_MAX_COMPONENTS      ||
         (blue_c = dev_proc(dev, get_color_comp_index)(
                        dev,
                        "Blue",
                        sizeof("Blue") - 1,
                        NO_COMP_NAME_TYPE )) < 0               ||
         blue_c == GX_DEVICE_COLOR_MAX_COMPONENTS        )
        return 0;


    if ( (pprocs = dev_proc(dev, get_color_mapping_procs)(dev)) == 0 ||
         (map_rgb = pprocs->map_rgb) == 0                            )
        return 0;

    map_rgb(dev, NULL, frac_14, frac_0, frac_0, out);
    if (!check_single_comp(red_c, frac_14, ncomps, out))
        return 0;
    map_rgb(dev, NULL, frac_0, frac_14, frac_0, out);
    if (!check_single_comp(green_c, frac_14, ncomps, out))
        return 0;
    map_rgb(dev, NULL, frac_0, frac_0, frac_14, out);
    if (!check_single_comp(blue_c, frac_14, ncomps, out))
        return 0;

    process_comps =  ((gx_color_index)1 << red_c)
                   | ((gx_color_index)1 << green_c)
                   | ((gx_color_index)1 << blue_c);
    pcinfo->opmode = GC_CINFO_OPMODE_RGB_SET;
    pcinfo->process_comps = process_comps;
    return process_comps;
}
