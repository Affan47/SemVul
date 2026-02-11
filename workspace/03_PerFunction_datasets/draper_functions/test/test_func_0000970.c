HPDF_ResetStream  (HPDF_Doc     pdf)
{
    if (!HPDF_HasDoc (pdf))
        return HPDF_INVALID_DOCUMENT;

    if (!HPDF_Stream_Validate (pdf->stream))
        return HPDF_RaiseError (&pdf->error, HPDF_INVALID_OPERATION, 0);

    return HPDF_Stream_Seek (pdf->stream, 0, HPDF_SEEK_SET);
}
