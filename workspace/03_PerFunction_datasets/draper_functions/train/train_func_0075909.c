s_image_colors_convert_to_device_color(stream_image_colors_state * ss)
{
    gs_client_color cc;
    gx_device_color dc;
    int i, code;
    double v0 = (1 << ss->bits_per_sample) - 1;
    double v1 = (1 << ss->output_bits_per_sample) - 1;

    for (i = 0; i < ss->depth; i++)
        cc.paint.values[i] = ss->input_color[i] *
                (ss->Decode[i * 2 + 1] - ss->Decode[i * 2]) / v0 + ss->Decode[i * 2];

    code = ss->pcs->type->remap_color(&cc, ss->pcs, &dc, ss->pis,
                              ss->pdev, gs_color_select_texture);
    if (code < 0)
        return code;
    for (i = 0; i < ss->output_depth; i++) {
        uint m = (1 << ss->pdev->color_info.comp_bits[i]) - 1;
        uint w = (dc.colors.pure >> ss->pdev->color_info.comp_shift[i]) & m;

        ss->output_color[i] = (uint)(v1 * w / m + 0.5);
    }
    return 0;
}
