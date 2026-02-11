setup_unicode_decoder(i_ctx_t *i_ctx_p, ref *Decoding)
{
    gs_unicode_decoder *pud = gs_alloc_struct(imemory, gs_unicode_decoder,
                             &st_unicode_decoder, "setup_unicode_decoder");
    if (pud == NULL)
        return_error(e_VMerror);
    ref_assign_new(&pud->data, Decoding);
    ifont_dir->glyph_to_unicode_table = pud;
    return 0;
}
