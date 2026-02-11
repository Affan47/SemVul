gx_forward_fill_rectangle(gx_device * dev, int x, int y, int w, int h,
                          gx_color_index color)
{
    gx_device_forward * const fdev = (gx_device_forward *)dev;
    gx_device *tdev = fdev->target;

    if (tdev == 0)
        return_error(gs_error_Fatal);
    return dev_proc(tdev, fill_rectangle)(tdev, x, y, w, h, color);
}
