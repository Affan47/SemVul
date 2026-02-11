mem_true16_fill_rectangle(gx_device * dev,
                          int x, int y, int w, int h, gx_color_index color)
{
    gx_device_memory * const mdev = (gx_device_memory *)dev;
#if arch_is_big_endian
    const ushort color16 = (ushort)color;
#else
    const ushort color16 = (ushort)((color << 8) | (color >> 8));
#endif
    declare_scan_ptr(dest);

    fit_fill(dev, x, y, w, h);
    setup_rect(dest);
    if (w == 1) {
        while (h-- > 0) {
            *(ushort *)dest = color16;
            inc_ptr(dest, draster);
        }
    } else if ((color16 >> 8) == (color16 & 0xff)) {
        bytes_fill_rectangle(scan_line_base(mdev, y) + (x << 1), draster,
                             (byte)color, w << 1, h);
    } else {
        while (h-- > 0) {
            ushort *pptr = (ushort *) dest;
            int cnt = w;

            for (; cnt >= 4; pptr += 4, cnt -= 4)
                pptr[3] = pptr[2] = pptr[1] = pptr[0] = color16;
            switch (cnt) {
            case 3: pptr[2] = color16;
            case 2: pptr[1] = color16;
            case 1: pptr[0] = color16;
            case 0: DO_NOTHING;
            }
            inc_ptr(dest, draster);
        }
    }
    return 0;
}
