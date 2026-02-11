HPDF_CMapEncoder_InitAttr  (HPDF_Encoder  encoder)
{
    HPDF_CMapEncoderAttr encoder_attr;
    HPDF_UINT i;
    HPDF_UINT j;

    HPDF_PTRACE ((" HPDF_CMapEncoder_InitAttr\n"));

    if (encoder->attr)
        return HPDF_INVALID_ENCODER;

    encoder_attr = HPDF_GetMem(encoder->mmgr,
            sizeof(HPDF_CMapEncoderAttr_Rec));

    if (!encoder_attr)
        return encoder->error->error_no;

    HPDF_MemSet (encoder_attr, 0, sizeof(HPDF_CMapEncoderAttr_Rec));
    encoder->attr = encoder_attr;

    encoder_attr->writing_mode = HPDF_WMODE_HORIZONTAL;

    for (i = 0; i <= 255; i++) {
        for (j = 0; j <= 255; j++) {

            encoder_attr->unicode_map[i][j] = 0x25A1;
        }
    }


    encoder_attr->cmap_range = HPDF_List_New (encoder->mmgr,
                HPDF_DEF_RANGE_TBL_NUM);
    if (!encoder_attr->cmap_range)
        return encoder->error->error_no;

    encoder_attr->notdef_range = HPDF_List_New (encoder->mmgr,
                HPDF_DEF_ITEMS_PER_BLOCK);
    if (!encoder_attr->notdef_range)
        return encoder->error->error_no;

    encoder_attr->code_space_range = HPDF_List_New (encoder->mmgr,
                HPDF_DEF_ITEMS_PER_BLOCK);
    if (!encoder_attr->code_space_range)
        return encoder->error->error_no;

    return HPDF_OK;
}
