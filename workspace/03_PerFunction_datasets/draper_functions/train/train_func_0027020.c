HPDF_CIDFontDef_ChangeStyle  (HPDF_FontDef   fontdef,
                              HPDF_BOOL      bold,
                              HPDF_BOOL      italic)
{
    HPDF_PTRACE ((" HPDF_CIDFontDef_ChangeStyle\n"));

    if (!fontdef || !fontdef->attr)
        return HPDF_INVALID_FONTDEF_DATA;

    if (bold) {
        fontdef->stemv *= 2;
        fontdef->flags |= HPDF_FONT_FOURCE_BOLD;
    }

    if (italic) {
        fontdef->italic_angle -= 11;
        fontdef->flags |= HPDF_FONT_ITALIC;
    }

    return HPDF_OK;
}
