pattern_accum_fill_rectangle(gx_device * dev, int x, int y, int w, int h,
                             gx_color_index color)
{
    gx_device_pattern_accum *const padev = (gx_device_pattern_accum *) dev;

    if (padev->bits)
        (*dev_proc(padev->target, fill_rectangle))
            (padev->target, x, y, w, h, color);
    if (padev->mask)
        return (*dev_proc(padev->mask, fill_rectangle))
            ((gx_device *) padev->mask, x, y, w, h, (gx_color_index) 1);
     else
        return 0;
}
