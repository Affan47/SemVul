KSC_EUC_V_Init  (HPDF_Encoder  encoder)
{
    HPDF_CMapEncoderAttr attr;
    HPDF_STATUS ret;

    if ((ret = HPDF_CMapEncoder_InitAttr (encoder)) != HPDF_OK)
        return ret;

    attr = (HPDF_CMapEncoderAttr)encoder->attr;

    if (HPDF_CMapEncoder_AddCMap (encoder, CMAP_ARRAY_KSC_EUC_H) != HPDF_OK)
        return encoder->error->error_no;

    if (HPDF_CMapEncoder_AddCMap (encoder, CMAP_ARRAY_KSC_EUC_V) != HPDF_OK)
        return encoder->error->error_no;

    if ((ret = KSC_EUC_AddCodeSpaceRange (encoder)) != HPDF_OK)
        return ret;

    if (HPDF_CMapEncoder_AddNotDefRange (encoder, KSC_EUC_NOTDEF_RANGE)
                != HPDF_OK)
        return encoder->error->error_no;

    HPDF_CMapEncoder_SetUnicodeArray (encoder, KSC_EUC_UNICODE_ARRAY);

    attr->is_lead_byte_fn = KSC_EUC_IsLeadByte;
    attr->is_trial_byte_fn = KSC_EUC_IsTrialByte;
    HPDF_StrCpy (attr->registry, "Adobe", attr->registry +
                HPDF_LIMIT_MAX_NAME_LEN);
    HPDF_StrCpy (attr->ordering, "Korea1", attr->ordering +
                HPDF_LIMIT_MAX_NAME_LEN);
    attr->suppliment = 0;
    attr->writing_mode = HPDF_WMODE_VERTICAL;
    attr->uid_offset = 310;
    attr->xuid[0] = 1;
    attr->xuid[1] = 10;
    attr->xuid[2] = 25401;

    encoder->type = HPDF_ENCODER_TYPE_DOUBLE_BYTE;

    return HPDF_OK;
}
