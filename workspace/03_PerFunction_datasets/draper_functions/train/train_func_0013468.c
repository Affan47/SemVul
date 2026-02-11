psdf_setup_image_colors_filter(psdf_binary_writer *pbw,
                               gx_device_psdf *pdev, gs_pixel_image_t * pim,
                               const gs_imager_state *pis)
{
    int code;
    stream_state *ss = s_alloc_state(pdev->memory, s__image_colors_template.stype,
        "psdf_setup_image_colors_filter");
    int i;

    if (ss == 0)
        return_error(gs_error_VMerror);
    pbw->memory = pdev->memory;
    pbw->dev = pdev;
    code = psdf_encode_binary(pbw, &s__image_colors_template, ss);
    if (code < 0)
        return code;
    s_image_colors_set_dimensions((stream_image_colors_state *)ss,
                    pim->Width, pim->Height,
                    gs_color_space_num_components(pim->ColorSpace),
                    pim->BitsPerComponent);
    s_image_colors_set_color_space((stream_image_colors_state *)ss,
                    (gx_device *)pdev, pim->ColorSpace, pis, pim->Decode);
    pim->BitsPerComponent = pdev->color_info.comp_bits[0];
    for (i = 0; i < pdev->color_info.num_components; i++) {
        pim->Decode[i * 2 + 0] = 0;
        pim->Decode[i * 2 + 1] = 1;
    }
    return 0;
}
