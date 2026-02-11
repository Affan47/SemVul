HPDF_Page_TextWidth  (HPDF_Page        page,
                      const char      *text)
{
    HPDF_PageAttr attr;
    HPDF_TextWidth tw;
    HPDF_REAL ret = 0;
    HPDF_UINT len = HPDF_StrLen(text, HPDF_LIMIT_MAX_STRING_LEN + 1);

    HPDF_PTRACE((" HPDF_Page_TextWidth\n"));

    if (!HPDF_Page_Validate (page) || len == 0)
        return 0;

    attr = (HPDF_PageAttr )page->attr;


    if (!attr->gstate->font) {
        HPDF_RaiseError (page->error, HPDF_PAGE_FONT_NOT_FOUND, 0);
        return 0;
    }

    tw = HPDF_Font_TextWidth (attr->gstate->font, (HPDF_BYTE *)text, len);

    ret += attr->gstate->word_space * tw.numspace;
    ret += tw.width * attr->gstate->font_size  / 1000;
    ret += attr->gstate->char_space * tw.numchars;

    HPDF_CheckError (page->error);

    return ret;
}
