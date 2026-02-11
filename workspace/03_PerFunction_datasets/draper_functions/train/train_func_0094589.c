install_PS_charproc_accumulator(gx_device_pdf *pdev, gs_text_enum_t *pte,
                             gs_text_enum_t *pte_default, pdf_text_enum_t *const penum)
{
    int code;

    penum->returned.current_char = pte_default->returned.current_char;
    penum->returned.current_glyph = pte_default->returned.current_glyph;
    pdev->charproc_ctm = penum->pis->ctm;
    if (penum->current_font->FontType == ft_user_defined &&
        penum->outer_CID == GS_NO_GLYPH &&
            !(penum->pte_default->text.operation & TEXT_DO_CHARWIDTH)) {


        gs_matrix m;
        pdf_font_resource_t *pdfont;

        code = pdf_start_charproc_accum(pdev);
        if (code < 0)
            return code;


        pdev->width *= 100;
        pdev->height *= 100;

        pdf_viewer_state_from_imager_state(pdev, pte->pis, pte->pdcolor);


        pdev->state.line_params.half_width = -1;
        pdev->state.line_params.start_cap = gs_cap_unknown;
        pdev->state.line_params.end_cap = gs_cap_unknown;
        pdev->state.line_params.dash_cap = gs_cap_unknown;
        pdev->state.line_params.join = gs_join_unknown;
        pdev->state.line_params.miter_limit = -1;
        pdev->state.line_params.dash.pattern_size = -1;


        gs_make_identity(&m);


        gs_matrix_scale(&m, 100, 100, &m);
        gs_matrix_fixed_from_matrix(&penum->pis->ctm, &m);


        code = pdf_choose_output_char_code(pdev, penum, &penum->output_char_code);
        if (code < 0)
            return code;
        code = pdf_attached_font_resource(pdev, penum->current_font, &pdfont, NULL, NULL, NULL, NULL);
        if (code < 0)
            return code;
        pdev->font3 = (pdf_resource_t *)pdfont;
        pdev->substream_Resources = pdfont->u.simple.s.type3.Resources;
        penum->charproc_accum = true;
        return TEXT_PROCESS_RENDER;
    }
    return 0;
}
