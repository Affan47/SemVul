copy_glyph_cid0(gs_font *font, gs_glyph glyph, gs_font *copied, int options)
{
    gs_glyph_data_t gdata;
    gs_font_cid0 *fcid0 = (gs_font_cid0 *)font;
    gs_font_cid0 *copied0 = (gs_font_cid0 *)copied;
    int fdbytes = copied0->cidata.FDBytes;
    int fidx;
    int code;
    byte prefix[MAX_FDBytes];
    int i;

    gdata.memory = font->memory;
    code = fcid0->cidata.glyph_data((gs_font_base *)font, glyph,
                &gdata, &fidx);
    if (code < 0)
        return code;
    for (i = fdbytes - 1; i >= 0; --i, fidx >>= 8)
        prefix[i] = (byte)fidx;
    if (fidx != 0)
        return_error(gs_error_rangecheck);
    return copy_glyph_data(font, glyph, copied, options, &gdata, prefix, fdbytes);
}
