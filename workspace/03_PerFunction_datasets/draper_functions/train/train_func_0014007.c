complete_charproc(gx_device_pdf *pdev, gs_text_enum_t *pte,
                             gs_text_enum_t *pte_default, pdf_text_enum_t *const penum,
                             bool was_PS_type3)
{
    gs_const_string gnstr;
    int code;

    code = pdf_choose_output_glyph_hame(pdev, penum, &gnstr, pte_default->returned.current_glyph);
    if (code < 0) {
        return code;
    }

    if ((penum->current_font->FontType == ft_user_defined ||
       penum->current_font->FontType == ft_PCL_user_defined ||
       penum->current_font->FontType == ft_MicroType ||
       penum->current_font->FontType == ft_GL2_stick_user_defined ||
       penum->current_font->FontType == ft_GL2_531) &&
       stell(pdev->strm) == 0)
    {
        char glyph[256], FontName[gs_font_name_max + 1], KeyName[256];
        int len;

        len = min(gs_font_name_max, gnstr.size);
        memcpy(glyph, gnstr.data, len);
        glyph[len] = 0x00;
        len = min(gs_font_name_max, penum->current_font->font_name.size);
        memcpy(FontName, penum->current_font->font_name.chars, len);
        FontName[len] = 0x00;
        len = min(gs_font_name_max, penum->current_font->key_name.size);
        memcpy(KeyName, penum->current_font->key_name.chars, len);
        KeyName[len] = 0x00;

        emprintf4(pdev->memory,
            "ERROR: Page %d used undefined glyph '%s' from type 3 font '%s', key '%s'\n",
            pdev->next_page, glyph, FontName, KeyName);
            stream_puts(pdev->strm, "0 0 0 0 0 0 d1\n");
    }

    if (was_PS_type3) {


        pdev->width /= 100;
        pdev->height /= 100;
    }
    code = pdf_end_charproc_accum(pdev, penum->current_font, penum->cgp,
                pte_default->returned.current_glyph, penum->output_char_code, &gnstr);
    if (code < 0)
        return code;
    penum->charproc_accum = false;
    code = gx_default_text_restore_state(pte_default);
    if (code < 0)
        return code;
    gs_text_release(pte_default, "pdf_text_process");
    penum->pte_default = 0;

    return 0;
}
