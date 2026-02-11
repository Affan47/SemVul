pdf_put_pattern_mask(gx_device_pdf *pdev, const gx_color_tile *m_tile,
                     cos_stream_t **ppcs_mask)
{
    int w = m_tile->tmask.rep_width, h = m_tile->tmask.rep_height;
    gs_image1_t image;
    pdf_image_writer writer;
    int code;

    gs_image_t_init_mask_adjust(&image, true, false);
    pdf_set_pattern_image((gs_data_image_t *)&image, &m_tile->tmask);
    pdf_image_writer_init(&writer);
    if ((code = pdf_begin_write_image(pdev, &writer, gs_no_id, w, h, NULL, false)) < 0 ||
        (pdev->params.MonoImage.Encode &&
         (code = psdf_CFE_binary(&writer.binary[0], w, h, true)) < 0) ||
        (code = pdf_begin_image_data(pdev, &writer, (const gs_pixel_image_t *)&image, NULL, 0)) < 0
        )
        return code;

    if ((code = pdf_copy_mask_bits(writer.binary[0].strm, m_tile->tmask.data + (h - 1) * m_tile->tmask.raster, 0, -m_tile->tmask.raster, w, h, 0)) < 0 ||
        (code = pdf_end_image_binary(pdev, &writer, h)) < 0 ||
        (code = pdf_end_write_image(pdev, &writer)) < 0
        )
        return code;
    *ppcs_mask = (cos_stream_t *)writer.pres->object;
    return 0;
}
