HPDF_Page_GetTransMatrix  (HPDF_Page   page)
{
    HPDF_TransMatrix DEF_MATRIX = {1, 0, 0, 1, 0, 0};

    HPDF_PTRACE((" HPDF_Page_GetTransMatrix\n"));
    if (HPDF_Page_Validate (page)) {
        HPDF_PageAttr attr = (HPDF_PageAttr)page->attr;

        return attr->gstate->trans_matrix;
    } else
        return DEF_MATRIX;
}
