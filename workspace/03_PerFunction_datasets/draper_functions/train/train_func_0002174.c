HPDF_ReadFromStream  (HPDF_Doc       pdf,
                      HPDF_BYTE     *buf,
                      HPDF_UINT32   *size)
{
    HPDF_UINT isize = *size;
    HPDF_STATUS ret;

    if (!HPDF_HasDoc (pdf))
        return HPDF_INVALID_DOCUMENT;

    if (!HPDF_Stream_Validate (pdf->stream))
        return HPDF_RaiseError (&pdf->error, HPDF_INVALID_OPERATION, 0);

    if (*size == 0)
        return HPDF_RaiseError (&pdf->error, HPDF_INVALID_PARAMETER, 0);

    ret = HPDF_Stream_Read (pdf->stream, buf, &isize);

    *size = isize;

    if (ret != HPDF_OK)
        HPDF_CheckError (&pdf->error);

    return ret;
}
