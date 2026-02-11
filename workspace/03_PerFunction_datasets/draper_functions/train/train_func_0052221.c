psd_get_color_comp_index(gx_device * dev, const char * pname,
                                        int name_size, int component_type)
{
    int index;
    psd_device *pdev = (psd_device *)dev;

    if (strncmp(pname, "None", name_size) == 0) return -1;
    index = devn_get_color_comp_index(dev,
                &(((psd_device *)dev)->devn_params),
                &(((psd_device *)dev)->equiv_cmyk_colors),
                pname, name_size, component_type, ENABLE_AUTO_SPOT_COLORS);


    if (index < 0 && component_type == SEPARATION_NAME &&
        pdev->warning_given == false &&
        pdev->devn_params.num_separation_order_names == 0) {
        dmlprintf(dev->memory, "**** Max spot colorants reached.\n");
        dmlprintf(dev->memory, "**** Some colorants will be converted to equivalent CMYK values.\n");
        dmlprintf(dev->memory, "**** If this is a Postscript file, try using the -dMaxSpots= option.\n");
        pdev->warning_given = true;
    }
    return index;
}
