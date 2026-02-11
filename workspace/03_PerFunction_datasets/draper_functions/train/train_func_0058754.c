pdf_text_release(gs_text_enum_t *pte, client_name_t cname)
{
    pdf_text_enum_t *const penum = (pdf_text_enum_t *)pte;

    if (penum->pte_default) {
        gs_text_release(penum->pte_default, cname);
        penum->pte_default = 0;
    }
    pdf_text_release_cgp(penum);
    gx_default_text_release(pte, cname);
}
