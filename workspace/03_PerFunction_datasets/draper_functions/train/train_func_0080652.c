expand_CIDMap(gs_font_cid2 *copied2, uint CIDCount)
{
    ushort *CIDMap;
    gs_copied_font_data_t *const cfdata = cf_data((gs_font *)copied2);

    if (CIDCount <= copied2->cidata.common.CIDCount)
        return 0;
    CIDMap = (ushort *)
        gs_alloc_byte_array(copied2->memory, CIDCount, sizeof(ushort),
                            "copy_font_cid2(CIDMap");
    if (CIDMap == 0)
        return_error(gs_error_VMerror);
    memcpy(CIDMap, cfdata->CIDMap, copied2->cidata.common.CIDCount * sizeof(*CIDMap));
    memset(CIDMap + copied2->cidata.common.CIDCount, 0xFF,
            (CIDCount - copied2->cidata.common.CIDCount) * sizeof(*CIDMap));
    cfdata->CIDMap = CIDMap;
    copied2->cidata.common.CIDCount = CIDCount;
    return 0;
}
