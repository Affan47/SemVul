unpack_scanline_lt8(
    gx_color_index *    destp,
    const byte *        srcp,
    int                 src_offset,
    int                 width,
    int                 depth )
{
    byte                buff = 0;
    int                 i = 0, shift = 8 - depth, p_per_byte = 8 / depth;


    if (width == 0)
        return;


    if (src_offset >= p_per_byte) {
        srcp += src_offset / p_per_byte;
        src_offset &= (p_per_byte - 1);
    }
    if (src_offset > 0) {
        buff = *srcp++ << (src_offset * depth);
        i = src_offset;
        width += src_offset;
    }


    for (; i < width; i++, buff <<= depth) {
        if ((i & (p_per_byte - 1)) == 0)
            buff = *srcp++;
        *destp++ = buff >> shift;
    }
}
