gx_copy_mono_unaligned(gx_device * dev, const byte * data,
            int dx, int raster, gx_bitmap_id id, int x, int y, int w, int h,
                       gx_color_index zero, gx_color_index one)
{
    dev_proc_copy_mono((*copy_mono)) = dev_proc(dev, copy_mono);
    uint offset = ALIGNMENT_MOD(data, align_bitmap_mod);
    int step = raster & (align_bitmap_mod - 1);


    data -= offset;
    dx += offset << 3;


    if (!step) {
        return (*copy_mono) (dev, data, dx, raster, id,
                             x, y, w, h, zero, one);
    }

    {
        const byte *p = data;
        int d = dx;
        int code = 0;
        int i;

        for (i = 0; i < h && code >= 0;
             ++i, p += raster - step, d += step << 3
            )
            code = (*copy_mono) (dev, p, d, raster, gx_no_bitmap_id,
                                 x, y + i, w, 1, zero, one);
        return code;
    }
}
