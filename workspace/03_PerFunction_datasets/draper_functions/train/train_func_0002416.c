HPDF_Page_EofillStroke  (HPDF_Page  page)
{
    HPDF_STATUS ret = HPDF_Page_CheckState (page, HPDF_GMODE_PATH_OBJECT |
            HPDF_GMODE_CLIPPING_PATH);
    HPDF_PageAttr attr;

    HPDF_PTRACE ((" HPDF_Page_EofillStroke\n"));

    if (ret != HPDF_OK)
        return ret;

    attr = (HPDF_PageAttr)page->attr;

    if (HPDF_Stream_WriteStr (attr->stream, "B*\012") != HPDF_OK)
        return HPDF_CheckError (page->error);

    attr->gmode = HPDF_GMODE_PAGE_DESCRIPTION;

    return ret;
}
