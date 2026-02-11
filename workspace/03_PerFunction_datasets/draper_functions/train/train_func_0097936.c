pack_scanline_lt8(
    const gx_color_index *  srcp,
    byte *                  destp,
    int                     dest_offset,
    int                     width,
    int                     depth )
{
    byte                    buff = 0;
    int                     i = 0, p_per_byte = 8 / depth;


    if (width == 0)
        return;


    if (dest_offset >= p_per_byte) {
        destp += dest_offset / p_per_byte;
        dest_offset &= (p_per_byte - 1);
    }
    if (dest_offset > 0) {
        buff = *destp++ >> (8 - dest_offset * depth);
        i = dest_offset;
        width += dest_offset;
    }


    for (; i < width; i++) {
        buff = (buff << depth) | *srcp++;
        if ((i & (p_per_byte - 1)) == p_per_byte - 1)
            *destp++ = buff;
    }
    if ((i &= (p_per_byte - 1)) != 0) {
        int     shift = depth * (p_per_byte - i);
        int     mask = (1 << shift) - 1;

        *destp = (*destp & mask) | (buff << shift);
    }
}
