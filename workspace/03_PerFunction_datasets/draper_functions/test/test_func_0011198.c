copy_glyph_cid2(gs_font *font, gs_glyph glyph, gs_font *copied, int options)
{
    gs_font_cid2 *fcid2 = (gs_font_cid2 *)font;
    gs_copied_font_data_t *const cfdata = cf_data(copied);
    gs_font_cid2 *copied2 = (gs_font_cid2 *)copied;
    int gid;
    int code;

    if (!(options & COPY_GLYPH_BY_INDEX)) {
        uint cid = glyph - GS_MIN_CID_GLYPH;
        int CIDCount;

        code = expand_CIDMap(copied2, cid + 1);
        if (code < 0)
            return code;
        CIDCount = copied2->cidata.common.CIDCount;
        gid = fcid2->cidata.CIDMap_proc(fcid2, glyph);
        if (gid < 0 || gid >= cfdata->glyphs_size)
            return_error(gs_error_rangecheck);
        if (cid > CIDCount)
            return_error(gs_error_invalidaccess);
        if (cfdata->CIDMap[cid] != 0xffff && cfdata->CIDMap[cid] != gid)
            return_error(gs_error_invalidaccess);
        code = copy_glyph_type42(font, glyph, copied, options);
        if (code < 0)
            return code;
        cfdata->CIDMap[cid] = gid;
    } else {
        gid = glyph - GS_MIN_GLYPH_INDEX;
        if (gid < 0 || gid >= cfdata->glyphs_size)
            return_error(gs_error_rangecheck);
        code = copy_glyph_type42(font, glyph, copied, options);
        if (code < 0)
            return code;
    }
    return code;
}
