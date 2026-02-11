build_rgb_palette(uint8_t *palette, int has_alpha)
{
    uint32_t *pal;
    static const uint8_t pal_value[6] = { 0x00, 0x33, 0x66, 0x99, 0xcc, 0xff };
    int i, r, g, b;

    pal = (uint32_t *)palette;
    i = 0;
    for(r = 0; r < 6; r++) {
        for(g = 0; g < 6; g++) {
            for(b = 0; b < 6; b++) {
                pal[i++] = (0xff << 24) | (pal_value[r] << 16) |
                    (pal_value[g] << 8) | pal_value[b];
            }
        }
    }
    if (has_alpha)
        pal[i++] = 0;
    while (i < 256)
        pal[i++] = 0xff000000;
}
