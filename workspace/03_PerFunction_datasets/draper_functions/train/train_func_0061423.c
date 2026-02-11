cff_FDSelect_size(cff_writer_t *pcw, psf_glyph_enum_t *penum, uint *pformat)
{
    gs_font_cid0 *const pfont = (gs_font_cid0 *)pcw->pfont;
    gs_font_base *const pbfont = (gs_font_base *)pfont;
    gs_glyph glyph;
    int prev = -1;
    uint linear_size = 1, range_size = 5;
    int code;


    psf_enumerate_glyphs_reset(penum);
    while ((code = psf_enumerate_glyphs_next(penum, &glyph)) == 0) {
        int font_index;

        code = pfont->cidata.glyph_data(pbfont, glyph, NULL, &font_index);
        if (code >= 0) {
            if (font_index != prev)
                range_size += 3, prev = font_index;
            ++linear_size;
        }
    }
    if (range_size < linear_size) {
        *pformat = 3;
        return range_size;
    } else {
        *pformat = 0;
        return linear_size;
    }
}
