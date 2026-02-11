HPDF_LoadTTFontFromFile2 (HPDF_Doc         pdf,
                          const char      *file_name,
                          HPDF_UINT        index,
                          HPDF_BOOL        embedding)
{
    HPDF_Stream font_data;
    const char *ret;

    HPDF_PTRACE ((" HPDF_LoadTTFontFromFile2\n"));

    if (!HPDF_HasDoc (pdf))
        return NULL;


    font_data = HPDF_FileReader_New (pdf->mmgr, file_name);

    if (HPDF_Stream_Validate (font_data)) {
        ret = LoadTTFontFromStream2 (pdf, font_data, index, embedding, file_name);
    } else
        ret = NULL;

    if (!ret)
        HPDF_CheckError (&pdf->error);

    return ret;
}
