InternalSaveToStream  (HPDF_Doc      pdf,
                       HPDF_Stream   stream)
{
    HPDF_STATUS ret;

    if ((ret = WriteHeader (pdf, stream)) != HPDF_OK)
        return ret;


    if ((ret = PrepareTrailer (pdf)) != HPDF_OK)
        return ret;


    if (pdf->encrypt_on) {
        HPDF_Encrypt e= HPDF_EncryptDict_GetAttr (pdf->encrypt_dict);

        if ((ret = HPDF_Doc_PrepareEncryption (pdf)) != HPDF_OK)
            return ret;

        if ((ret = HPDF_Xref_WriteToStream (pdf->xref, stream, e)) != HPDF_OK)
            return ret;
    } else {
        if ((ret = HPDF_Xref_WriteToStream (pdf->xref, stream, NULL)) !=
                HPDF_OK)
            return ret;
    }

    return HPDF_OK;
}
