mem_mono_fill_rectangle(gx_device * dev, int x, int y, int w, int h,
                        gx_color_index color)
{
    gx_device_memory * const mdev = (gx_device_memory *)dev;

#ifdef DO_FILL_RECT_BY_COPY_ROP
    return mem_mono_strip_copy_rop(dev, NULL, 0, 0, gx_no_bitmap_id, NULL,
                             NULL, NULL,
                             x, y, w, h, 0, 0,
                             (color ? rop3_1 : rop3_0));
#else
    fit_fill(dev, x, y, w, h);
    bits_fill_rectangle(scan_line_base(mdev, y), x, mdev->raster,
                        -(int)(mono_fill_chunk) color, w, h);
    return 0;
#endif
}
