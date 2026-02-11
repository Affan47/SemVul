HPDF_Page_GetLineJoin  (HPDF_Page   page)
{
    HPDF_PTRACE((" HPDF_Page_GetLineJoin\n"));

    if (HPDF_Page_Validate (page)) {
        HPDF_PageAttr attr = (HPDF_PageAttr)page->attr;

        return attr->gstate->line_join;
    } else
        return HPDF_DEF_LINEJOIN;
}
