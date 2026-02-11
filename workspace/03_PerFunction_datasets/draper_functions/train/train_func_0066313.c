HPDF_Page_GetCurrentFontSize  (HPDF_Page   page)
{
    HPDF_PTRACE((" HPDF_Page_GetCurrentFontSize\n"));

    if (HPDF_Page_Validate (page)) {
        HPDF_PageAttr attr = (HPDF_PageAttr)page->attr;

        return (attr->gstate->font) ? attr->gstate->font_size : 0;
    } else
        return 0;
}
