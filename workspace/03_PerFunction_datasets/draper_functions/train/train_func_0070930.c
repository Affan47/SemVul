pdf_font_simple_alloc(gx_device_pdf *pdev, pdf_font_resource_t **ppfres,
                      gs_id rid, pdf_font_descriptor_t *pfd)
{
    pdf_font_resource_t *pdfont;
    int code;

    code = font_resource_encoded_alloc(pdev, &pdfont, rid,
                                           pdf_font_descriptor_FontType(pfd),
                                           pdf_write_contents_simple);

    if (code < 0)
        return(gs_note_error(code));
    pdfont->FontDescriptor = pfd;
    set_is_MM_instance(pdfont, pdf_font_descriptor_font(pfd, false));
    *ppfres = pdfont;
    return pdf_compute_BaseFont(pdev, pdfont, false);
}
