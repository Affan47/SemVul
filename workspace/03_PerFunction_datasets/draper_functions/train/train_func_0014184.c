gs_type42_font_init_compare (const void *a, const void *b)
{
    ulong a_offset = ((const gs_type42_font_init_sort_t *)a)->glyph_offset;
    ulong b_offset = ((const gs_type42_font_init_sort_t *)b)->glyph_offset;
    if (a_offset < b_offset)
        return -1;
    else if (a_offset > b_offset)
        return +1;
    else

        return ((const gs_type42_font_init_sort_t *)a)->glyph_num -
               ((const gs_type42_font_init_sort_t *)b)->glyph_num;
}
