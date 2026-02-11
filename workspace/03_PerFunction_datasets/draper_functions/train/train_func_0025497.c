cff_write_Top_fdarray(cff_writer_t *pcw, gs_font_base *pbfont,
                      uint Private_offset, uint Private_size)
{
    const gs_font_name *pfname = &pbfont->font_name;
    gs_font_info_t info;

    cff_get_Top_info_common(pcw, pbfont, false, &info);
    cff_write_Top_common(pcw, pbfont, false, &info);
    cff_put_int(pcw, Private_size);
    cff_put_int_value(pcw, Private_offset, TOP_Private);
    if (pfname->size == 0)
        pfname = &pbfont->key_name;
    if (pfname->size) {
        cff_put_string(pcw, pfname->chars, pfname->size);
        cff_put_op(pcw, TOP_FontName);
    }
}
