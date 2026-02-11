gx_forward_copy_color(gx_device * dev, const byte * data,
                      int dx, int raster, gx_bitmap_id id,
                      int x, int y, int w, int h)
{
    gx_device_forward * const fdev = (gx_device_forward *)dev;
    gx_device *tdev = fdev->target;

    if (tdev == 0)
        return_error(gs_error_Fatal);
    return dev_proc(tdev, copy_color)
        (tdev, data, dx, raster, id, x, y, w, h);
}
