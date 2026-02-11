show_set_encode_char(gs_show_enum * penum)
{
    penum->encode_char =
        (SHOW_IS(penum, TEXT_FROM_GLYPHS | TEXT_FROM_SINGLE_GLYPH) ?
         gs_no_encode_char :
         gs_show_current_font(penum)->procs.encode_char);
}
