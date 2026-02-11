copied_cid2_CIDMap_proc(gs_font_cid2 *fcid2, gs_glyph glyph)
{
    uint cid = glyph - GS_MIN_CID_GLYPH;
    gs_copied_font_data_t *const cfdata = cf_data((gs_font *)fcid2);
    const ushort *CIDMap = cfdata->CIDMap;

    if (glyph < GS_MIN_CID_GLYPH || cid >= fcid2->cidata.common.CIDCount)
        return_error(gs_error_rangecheck);
    if (CIDMap[cid] == 0xffff)
        return -1;
    return CIDMap[cid];
}
