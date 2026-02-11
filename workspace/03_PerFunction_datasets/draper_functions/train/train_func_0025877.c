glyph_data_substring_by_font(gs_glyph_data_t *pgd, uint offset, uint size)
{
    gs_font *const font = pgd->proc_data;
    byte *data = (byte *)pgd->bits.data;

    if (pgd->bits.bytes)
        return glyph_data_substring_permanent(pgd, offset, size);
    if (offset > 0)
        memmove(data, data + offset, size);
    pgd->bits.data =
        gs_resize_string(font->memory, data, pgd->bits.size, size,
                         "glyph_data_substring");
    pgd->bits.size = size;
    return 0;
}
