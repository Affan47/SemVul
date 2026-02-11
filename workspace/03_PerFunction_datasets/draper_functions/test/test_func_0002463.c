display_update_spot_equivalent_colors(gx_device * dev, const gs_state * pgs)
{
    gx_device_display * ddev = (gx_device_display *)dev;

    if ((ddev->nFormat & DISPLAY_COLORS_MASK) == DISPLAY_COLORS_SEPARATION)
        update_spot_equivalent_cmyk_colors(dev, pgs,
                    &ddev->devn_params, &ddev->equiv_cmyk_colors);
    return 0;
}
