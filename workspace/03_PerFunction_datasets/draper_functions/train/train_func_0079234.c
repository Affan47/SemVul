pattern_accum_copy_planes(gx_device * dev, const byte * data, int data_x,
                          int raster, gx_bitmap_id id,
                          int x, int y, int w, int h, int plane_height)
{
    gx_device_pattern_accum *const padev = (gx_device_pattern_accum *) dev;

    if (padev->bits)
        (*dev_proc(padev->target, copy_planes))
            (padev->target, data, data_x, raster, id, x, y, w, h, plane_height);
    if (padev->mask)
        return (*dev_proc(padev->mask, fill_rectangle))
            ((gx_device *) padev->mask, x, y, w, h, (gx_color_index) 1);
    else
        return 0;
}
