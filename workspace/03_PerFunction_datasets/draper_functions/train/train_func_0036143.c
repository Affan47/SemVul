complete_adding_char(gx_device_pdf *pdev, gs_font *font,
                     gs_glyph glyph, gs_char ch, pdf_char_proc_t *pcp,
                     const gs_const_string *gnstr)
{
    pdf_font_resource_t *pdfont;
    double *real_widths;
    byte *glyph_usage;
    int char_cache_size, width_cache_size;
    pdf_encoding_element_t *pet;
    int code;

    code = pdf_attached_font_resource(pdev, font, &pdfont,
                &glyph_usage, &real_widths, &char_cache_size, &width_cache_size);
    if (code < 0)
        return code;
    code = pdf_attach_charproc(pdev, pdfont, pcp, glyph, ch, gnstr);
    if (code < 0)
        return code;
    if (ch >= char_cache_size || ch >= width_cache_size)
        return_error(gs_error_unregistered);
    pet = &pdfont->u.simple.Encoding[ch];
    pdfont->Widths[ch] = pcp->real_width.x;
    real_widths[ch * 2    ] = pcp->real_width.x;
    real_widths[ch * 2 + 1] = pcp->real_width.y;
    glyph_usage[ch / 8] |= 0x80 >> (ch & 7);
    pdfont->used[ch >> 3] |= 0x80 >> (ch & 7);
    if (pdfont->u.simple.v != NULL && font->WMode) {
        pdfont->u.simple.v[ch].x = pcp->v.x;
        pdfont->u.simple.v[ch].y = pcp->v.x;
    }
    pet->glyph = glyph;
    pet->str = *gnstr;
    pet->is_difference = true;
    if (pdfont->u.simple.LastChar < (int)ch)
        pdfont->u.simple.LastChar = (int)ch;
    if (pdfont->u.simple.FirstChar > (int)ch)
        pdfont->u.simple.FirstChar = (int)ch;
    return 0;
}
