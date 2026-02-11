aes_update_utf8(struct aes *aes, const char *utf8)
{
    if (utf8 == NULL) {
        aes->aes_set = 0;
        return (1);
    }


    archive_strcpy(&(aes->aes_utf8), utf8);


    archive_string_empty(&(aes->aes_mbs));
    if (aes->aes_wcs) {
        free((wchar_t *)(uintptr_t)aes->aes_wcs);
        aes->aes_wcs = NULL;
    }

    aes->aes_set = AES_SET_UTF8;


    aes->aes_wcs = __archive_string_utf8_w(&(aes->aes_utf8));
    if (aes->aes_wcs == NULL)
        return (0);
    aes->aes_set = AES_SET_UTF8 | AES_SET_WCS;


    if (archive_strappend_w_mbs(&(aes->aes_mbs), aes->aes_wcs) == NULL)
        return (0);
    aes->aes_set = AES_SET_UTF8 | AES_SET_WCS | AES_SET_MBS;


    return (1);
}
