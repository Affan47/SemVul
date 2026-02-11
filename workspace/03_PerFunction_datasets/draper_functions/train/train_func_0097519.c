HPDF_FontDef_Cleanup (HPDF_FontDef  fontdef)
{
    if (!fontdef)
        return;

    HPDF_PTRACE ((" HPDF_FontDef_Cleanup\n"));

    if (fontdef->clean_fn)
        fontdef->clean_fn (fontdef);

    fontdef->descriptor = NULL;
}
