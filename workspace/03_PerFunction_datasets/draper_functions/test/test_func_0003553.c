HPDF_Page_GetCMYKStroke  (HPDF_Page   page)
{
    HPDF_CMYKColor DEF_CMYK_COLOR = {0, 0, 0, 0};

    HPDF_PTRACE((" HPDF_Page_GetCMYKStroke\n"));

    if (HPDF_Page_Validate (page)) {
        HPDF_PageAttr attr = (HPDF_PageAttr)page->attr;

        if (attr->gstate->cs_stroke == HPDF_CS_DEVICE_CMYK)
            return attr->gstate->cmyk_stroke;
    }

    return DEF_CMYK_COLOR;
}
