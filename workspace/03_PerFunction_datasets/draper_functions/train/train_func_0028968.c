HPDF_Page_SetFontAndSize  (HPDF_Page  page,
                           HPDF_Font  font,
                           HPDF_REAL  size)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PAGE_DESCRIPTION |
                    HPDF_GMODE_TEXT_OBJECT);
    char buf[HPDF_TMP_BUF_SIZ];
    char *pbuf = buf;
    char *eptr = buf + HPDF_TMP_BUF_SIZ - 1;
    const char *local_name;
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_SetFontAndSize\n"));

    if (ret != HPDF_OK)
        return ret;

    if (!HPDF_Font_Validate (font))
        return HPDF_RaiseError (page->error, HPDF_PAGE_INVALID_FONT, 0);

    if (size <= 0 || size > HPDF_MAX_FONTSIZE)
        return HPDF_RaiseError (page->error, HPDF_PAGE_INVALID_FONT_SIZE, 0);

    if (page->mmgr != font->mmgr)
        return HPDF_RaiseError (page->error, HPDF_PAGE_INVALID_FONT, 0);

    attr = (HPDF_PageAttr)page->attr;
    local_name = HPDF_Page_GetLocalFontName (page, font);

    if (!local_name)
        return HPDF_RaiseError (page->error, HPDF_PAGE_INVALID_FONT, 0);

    if (HPDF_Stream_WriteEscapeName (attr->stream, local_name) != HPDF_OK)
        return HPDF_CheckError (page->error);

    HPDF_MemSet (buf, 0, HPDF_TMP_BUF_SIZ);
    *pbuf++ = ' ';
    pbuf = HPDF_FToA (pbuf, size, eptr);
    HPDF_StrCpy (pbuf, " Tf\012", eptr);

    if (HPDF_Stream_WriteStr (attr->stream, buf) != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->gstate->font = font;
    attr->gstate->font_size = size;
    attr->gstate->writing_mode = ((HPDF_FontAttr)font->attr)->writing_mode;

    return ret;
}
