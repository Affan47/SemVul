mem_true24_copy_alpha(gx_device * dev, const byte * base, int sourcex,
                   int sraster, gx_bitmap_id id, int x, int y, int w, int h,
                      gx_color_index color, int depth)
{
    gx_device_memory * const mdev = (gx_device_memory *)dev;
    const byte *line;

    declare_scan_ptr(dest);
    declare_unpack_color(r, g, b, color);

    fit_copy(dev, base, sourcex, sraster, id, x, y, w, h);
    setup_rect(dest);
    line = base;
    while (h-- > 0) {
        register byte *pptr = dest;
        int sx;

        for (sx = sourcex; sx < sourcex + w; ++sx, pptr += 3) {
            int alpha2, alpha;

            if (depth == 2)
                alpha =
                    ((line[sx >> 2] >> ((3 - (sx & 3)) << 1)) & 3) * 5;
            else
                alpha2 = line[sx >> 1],
                    alpha = (sx & 1 ? alpha2 & 0xf : alpha2 >> 4);
            if (alpha == 15) {
                put3(pptr, r, g, b);
            } else if (alpha != 0) {
#define make_shade(old, clr, alpha, amax) \
  (old) + (((int)(clr) - (int)(old)) * (alpha) / (amax))
                pptr[0] = make_shade(pptr[0], r, alpha, 15);
                pptr[1] = make_shade(pptr[1], g, alpha, 15);
                pptr[2] = make_shade(pptr[2], b, alpha, 15);
#undef make_shade
            }
        }
        line += sraster;
        inc_ptr(dest, draster);
    }
    return 0;
}
