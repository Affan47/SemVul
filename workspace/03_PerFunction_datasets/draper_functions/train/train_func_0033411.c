guess_palette(uint32_t *rgba_palette,
                          uint8_t *colormap,
                          uint8_t *alpha,
                          uint32_t subtitle_color)
{
    uint8_t color_used[16];
    int nb_opaque_colors, i, level, j, r, g, b;

    for(i = 0; i < 4; i++)
        rgba_palette[i] = 0;

    memset(color_used, 0, 16);
    nb_opaque_colors = 0;
    for(i = 0; i < 4; i++) {
        if (alpha[i] != 0 && !color_used[colormap[i]]) {
            color_used[colormap[i]] = 1;
            nb_opaque_colors++;
        }
    }

    if (nb_opaque_colors == 0)
        return;

    j = nb_opaque_colors;
    memset(color_used, 0, 16);
    for(i = 0; i < 4; i++) {
        if (alpha[i] != 0) {
            if (!color_used[colormap[i]])  {
                level = (0xff * j) / nb_opaque_colors;
                r = (((subtitle_color >> 16) & 0xff) * level) >> 8;
                g = (((subtitle_color >> 8) & 0xff) * level) >> 8;
                b = (((subtitle_color >> 0) & 0xff) * level) >> 8;
                rgba_palette[i] = b | (g << 8) | (r << 16) | ((alpha[i] * 17) << 24);
                color_used[colormap[i]] = (i + 1);
                j--;
            } else {
                rgba_palette[i] = (rgba_palette[color_used[colormap[i]] - 1] & 0x00ffffff) |
                                    ((alpha[i] * 17) << 24);
            }
        }
    }
}
