pdf_mark_text_glyphs(const gs_text_enum_t *penum, const gs_string *pstr,
            byte *glyph_usage, int char_cache_size)
{
    gs_text_enum_t scan = *penum;
    gs_font *font = (gs_font *)penum->current_font;
    bool font_is_simple = pdf_is_simple_font(font);
    gs_char char_code, cid;
    gs_glyph glyph;

    if (glyph_usage == NULL)
        return 0;

    if (pstr != NULL) {
        scan.text.data.bytes = pstr->data;
        scan.text.size = pstr->size;
        scan.index = 0;

        if ( scan.text.operation & TEXT_FROM_CHARS )
            scan.text.operation =
                ((scan.text.operation & ~TEXT_FROM_CHARS) | TEXT_FROM_STRING);
    }
    for (;;) {
        int code = pdf_next_char_glyph(&scan, pstr, font, font_is_simple,
                                       &char_code, &cid, &glyph);

        if (code == 2)
            break;
        if (code == 3)
            continue;
        if (code < 0)
            return code;
        if (cid >= char_cache_size)
            continue;
        glyph_usage[cid / 8] |= 0x80 >> (cid & 7);
    }
    return 0;
}
