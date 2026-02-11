copied_type1_subr_data(gs_font_type1 * pfont, int subr_num, bool global,
                       gs_glyph_data_t *pgd)
{
    gs_copied_font_data_t *const cfdata = cf_data((gs_font *)pfont);
    const gs_subr_info_t *psi =
        (global ? &cfdata->global_subrs : &cfdata->subrs);

    if (subr_num < 0 || subr_num >= psi->count)
        return_error(gs_error_rangecheck);
    gs_glyph_data_from_string(pgd, psi->data + psi->starts[subr_num],
                              psi->starts[subr_num + 1] -
                                psi->starts[subr_num],
                              NULL);
    return 0;
}
