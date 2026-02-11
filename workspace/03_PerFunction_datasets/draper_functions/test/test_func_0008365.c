HPDF_SetPermission  (HPDF_Doc    pdf,
                     HPDF_UINT   permission)
{
    HPDF_Encrypt e;

    HPDF_PTRACE ((" HPDF_SetPermission\n"));

    if (!HPDF_HasDoc (pdf))
        return HPDF_DOC_INVALID_OBJECT;

    e = HPDF_EncryptDict_GetAttr (pdf->encrypt_dict);

    if (!e)
        return HPDF_RaiseError (&pdf->error,
                HPDF_DOC_ENCRYPTDICT_NOT_FOUND, 0);
    else
        e->permission = permission;

    return HPDF_OK;
}
