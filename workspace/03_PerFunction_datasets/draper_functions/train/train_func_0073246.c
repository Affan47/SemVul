cff_convert_charstrings(const cff_writer_t *pcw, const gs_font_base *pfont)
{
    return (pfont->FontType != ft_encrypted2 &&
            (pcw->options & WRITE_TYPE2_CHARSTRINGS) != 0);
}
