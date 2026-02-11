copied_type42_encode_char(gs_font *copied, gs_char chr,
                          gs_glyph_space_t glyph_space)
{
    gs_copied_font_data_t *const cfdata = cf_data(copied);
    const gs_glyph *Encoding = cfdata->Encoding;
    gs_glyph glyph;

    if (chr >= 256 || Encoding == 0)
        return GS_NO_GLYPH;
    glyph = Encoding[chr];
    if (glyph_space == GLYPH_SPACE_INDEX) {

        gs_copied_glyph_t *pcg;
        int code = named_glyph_slot_linear(cfdata, glyph, &pcg);

        if (code < 0 || !pcg->used)
            return GS_NO_GLYPH;
        return GS_MIN_GLYPH_INDEX + (pcg - cfdata->glyphs);
    }
    return glyph;
}
