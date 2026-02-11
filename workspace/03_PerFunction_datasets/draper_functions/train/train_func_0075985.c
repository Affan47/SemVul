x_clear_color_cache(gx_device   * dev)
{
    gx_device_X_wrapper *xdev = (gx_device_X_wrapper *) dev;
    int i;

    for (i = 0; i < countof(xdev->color_cache); ++i)
        xdev->color_cache[i] = gx_no_color_index;
    gx_device_decache_colors(dev);
}
