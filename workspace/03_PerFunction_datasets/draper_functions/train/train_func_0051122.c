mem_true16_copy_mono(gx_device * dev,
                     const byte * base, int sourcex, int sraster,
                     gx_bitmap_id id, int x, int y, int w, int h,
                     gx_color_index zero, gx_color_index one)
{
    gx_device_memory * const mdev = (gx_device_memory *)dev;
#if arch_is_big_endian
    const ushort zero16 = (ushort)zero;
    const ushort one16 = (ushort)one;
#else
    ushort zero16 = ((uint) (byte) zero << 8) + ((ushort) zero >> 8);
    ushort one16 = ((uint) (byte) one << 8) + ((ushort) one >> 8);
#endif
    const byte *line;
    int first_bit;

    declare_scan_ptr(dest);
    fit_copy(dev, base, sourcex, sraster, id, x, y, w, h);
    setup_rect(dest);
    line = base + (sourcex >> 3);
    first_bit = 0x80 >> (sourcex & 7);
    while (h-- > 0) {
        register ushort *pptr = (ushort *) dest;
        const byte *sptr = line;
        register int sbyte = *sptr++;
        register int bit = first_bit;
        int count = w;

        do {
            if (sbyte & bit) {
                if (one != gx_no_color_index)
                    *pptr = one16;
            } else {
                if (zero != gx_no_color_index)
                    *pptr = zero16;
            }
            if ((bit >>= 1) == 0)
                bit = 0x80, sbyte = *sptr++;
            pptr++;
        }
        while (--count > 0);
        line += sraster;
        inc_ptr(dest, draster);
    }
    return 0;
}
