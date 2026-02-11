UTF8_Init  (HPDF_Encoder  encoder)
{
    HPDF_CMapEncoderAttr attr;
    HPDF_STATUS ret;

    if ((ret = HPDF_CMapEncoder_InitAttr (encoder)) != HPDF_OK)
        return ret;

    attr = (HPDF_CMapEncoderAttr)encoder->attr;

    if (HPDF_CMapEncoder_AddCMap (encoder, CMAP_ARRAY_UTF8) != HPDF_OK)
        return encoder->error->error_no;

    if ((ret = UTF8_AddCodeSpaceRange (encoder)) != HPDF_OK)
        return ret;

    if (HPDF_CMapEncoder_AddNotDefRange (encoder, UTF8_NOTDEF_RANGE)
                != HPDF_OK)
        return encoder->error->error_no;

    HPDF_CMapEncoder_SetUnicodeArray (encoder, UTF8_UNICODE_ARRAY);

    attr->is_lead_byte_fn = UTF8_IsLeadByte;
    attr->is_trial_byte_fn = UTF8_IsTrialByte;

    HPDF_StrCpy (attr->registry, "Adobe", attr->registry +
                HPDF_LIMIT_MAX_NAME_LEN);
    HPDF_StrCpy (attr->ordering, "UTF-8", attr->ordering +
                HPDF_LIMIT_MAX_NAME_LEN);
    attr->suppliment = 0;
    attr->writing_mode = HPDF_WMODE_HORIZONTAL;


    encoder->type = HPDF_ENCODER_TYPE_DOUBLE_BYTE;

    return HPDF_OK;
}
