HPDF_PDFA_GenerateID(HPDF_Doc pdf)
{
    HPDF_Array id;
    HPDF_BYTE *currentTime;
    HPDF_BYTE idkey[HPDF_MD5_KEY_LEN];
    HPDF_MD5_CTX md5_ctx;
    time_t ltime;

    ltime = time(NULL);
    currentTime = (HPDF_BYTE *)ctime(&ltime);

    id = HPDF_Dict_GetItem(pdf->trailer, "ID", HPDF_OCLASS_ARRAY);
    if (!id) {
       id = HPDF_Array_New(pdf->mmgr);

       if (!id || HPDF_Dict_Add(pdf->trailer, "ID", id) != HPDF_OK)
         return pdf->error.error_no;

       HPDF_MD5Init(&md5_ctx);
       HPDF_MD5Update(&md5_ctx, (HPDF_BYTE *) "libHaru", sizeof("libHaru") - 1);
       HPDF_MD5Update(&md5_ctx, currentTime, HPDF_StrLen((const char *)currentTime, -1));
       HPDF_MD5Final(idkey, &md5_ctx);

       if (HPDF_Array_Add (id, HPDF_Binary_New (pdf->mmgr, idkey, HPDF_MD5_KEY_LEN)) != HPDF_OK)
         return pdf->error.error_no;

       if (HPDF_Array_Add (id, HPDF_Binary_New (pdf->mmgr,idkey,HPDF_MD5_KEY_LEN)) != HPDF_OK)
         return pdf->error.error_no;

       return HPDF_OK;
    }

    return HPDF_OK;
}
