pdf_alloc_text_glyphs_table(gx_device_pdf *pdev, pdf_text_enum_t *penum, const gs_string *pstr)
{
    const int go = (pstr != NULL ? pstr->size : penum->text.size);
    const int struct_size = sizeof(pdf_char_glyph_pairs_t) +
                            sizeof(pdf_char_glyph_pair_t) * (2 * go - 1);
    pdf_char_glyph_pairs_t *cgp = (pdf_char_glyph_pairs_t *)gs_alloc_bytes(penum->memory,
                struct_size, "pdf_alloc_text_glyphs_table");
    if (cgp == NULL)
        return_error(gs_error_VMerror);
    penum->cgp = cgp;
    cgp->unused_offset = go;
    cgp->num_all_chars = 0;
    cgp->num_unused_chars = 0;
    return 0;
}
