HPDF_Doc_FindFont  (HPDF_Doc          pdf,
                    const char  *font_name,
                    const char  *encoding_name)
{
    HPDF_UINT i;
    HPDF_Font font;

    HPDF_PTRACE ((" HPDF_Doc_FindFont\n"));

    for (i = 0; i < pdf->font_mgr->count; i++) {
        HPDF_FontAttr attr;

        font = (HPDF_Font)HPDF_List_ItemAt (pdf->font_mgr, i);
        attr = (HPDF_FontAttr) font->attr;

        if (HPDF_StrCmp (attr->fontdef->base_font, font_name) == 0 &&
                HPDF_StrCmp (attr->encoder->name, encoding_name) == 0)
            return font;
    }

    return NULL;
}
