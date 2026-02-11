pdf_exit_substream(gx_device_pdf *pdev)
{
    int code, code1;
    int sbstack_ptr;

    if (pdev->sbstack_depth <= 0)
        return_error(gs_error_unregistered);
    code = pdf_open_contents(pdev, PDF_IN_STREAM);
    sbstack_ptr = pdev->sbstack_depth - 1;
    while (pdev->vgstack_depth > pdev->vgstack_bottom) {
        code1 = pdf_restore_viewer_state(pdev, pdev->strm);
        if (code >= 0)
            code = code1;
    }
    if (pdev->clip_path != 0)
        gx_path_free(pdev->clip_path, "pdf_end_charproc_accum");
    code1 = pdf_close_aside(pdev);
    if (code1 < 0 && code >= 0)
        code = code1;
    pdev->context = pdev->sbstack[sbstack_ptr].context;
    pdf_text_state_copy(pdev->text->text_state, pdev->sbstack[sbstack_ptr].text_state);
    pdev->clip_path = pdev->sbstack[sbstack_ptr].clip_path;
    pdev->sbstack[sbstack_ptr].clip_path = 0;
    pdev->clip_path_id = pdev->sbstack[sbstack_ptr].clip_path_id;
    pdev->vgstack_bottom = pdev->sbstack[sbstack_ptr].vgstack_bottom;
    pdev->strm = pdev->sbstack[sbstack_ptr].strm;
    pdev->sbstack[sbstack_ptr].strm = 0;
    pdev->procsets = pdev->sbstack[sbstack_ptr].procsets;
    pdev->substream_Resources = pdev->sbstack[sbstack_ptr].substream_Resources;
    pdev->sbstack[sbstack_ptr].substream_Resources = 0;
    pdev->skip_colors = pdev->sbstack[sbstack_ptr].skip_colors;
    pdev->font3 = pdev->sbstack[sbstack_ptr].font3;
    pdev->sbstack[sbstack_ptr].font3 = 0;
    pdev->accumulating_substream_resource = pdev->sbstack[sbstack_ptr].accumulating_substream_resource;
    pdev->sbstack[sbstack_ptr].accumulating_substream_resource = 0;
    pdev->charproc_just_accumulated = pdev->sbstack[sbstack_ptr].charproc_just_accumulated;
    pdev->accumulating_a_global_object = pdev->sbstack[sbstack_ptr].accumulating_a_global_object;
    pdev->pres_soft_mask_dict = pdev->sbstack[sbstack_ptr].pres_soft_mask_dict;
    pdev->objname = pdev->sbstack[sbstack_ptr].objname;
    pdev->last_charpath_op = pdev->sbstack[sbstack_ptr].last_charpath_op;
    pdev->sbstack_depth = sbstack_ptr;
    code1 = pdf_restore_viewer_state(pdev, NULL);
    if (code1 < 0 && code >= 0)
        code = code1;
    return code;
}
