pdf_put_uncolored_pattern(gx_device_pdf *pdev, const gx_drawing_color *pdc,
                          const gs_color_space *pcs,
                          const psdf_set_color_commands_t *ppscc,
                          bool have_pattern_streams, pdf_resource_t **ppres)
{
    const gx_color_tile *m_tile = pdc->mask.m_tile;
    gx_drawing_color dc_pure;

    if (!have_pattern_streams && m_tile == 0) {


        *ppres = 0;
        set_nonclient_dev_color(&dc_pure, gx_dc_pure_color(pdc));
        return psdf_set_color((gx_device_vector *)pdev, &dc_pure, ppscc);
    } else {
        cos_value_t v;
        stream *s = pdev->strm;
        int code;
        cos_stream_t *pcs_image;
        static const psdf_set_color_commands_t no_scc = {0, 0, 0};

        if (!tile_size_ok(pdev, NULL, m_tile))
            return_error(gs_error_limitcheck);
        if (!have_pattern_streams) {
            if ((code = pdf_cs_Pattern_uncolored(pdev, &v)) < 0 ||
                (code = pdf_put_pattern_mask(pdev, m_tile, &pcs_image)) < 0 ||
                (code = pdf_pattern(pdev, pdc, NULL, m_tile, pcs_image, ppres)) < 0
                )
                return code;
        } else {
            code = pdf_cs_Pattern_uncolored_hl(pdev, pcs, &v);
            if (code < 0)
                return code;
            *ppres = pdf_find_resource_by_gs_id(pdev, resourcePattern, pdc->mask.id);
            *ppres = pdf_substitute_pattern(*ppres);
            if (!pdev->AR4_save_bug && pdev->CompatibilityLevel <= 1.3) {


                stream_puts(pdev->strm, "q q Q Q\n");
                pdev->AR4_save_bug = true;
            }
            (*ppres)->where_used |= pdev->used_mask;
        }
        cos_value_write(&v, pdev);
        pprints1(s, " %s ", ppscc->setcolorspace);
        if (have_pattern_streams)
            return 0;
        set_nonclient_dev_color(&dc_pure, gx_dc_pure_color(pdc));
        return psdf_set_color((gx_device_vector *)pdev, &dc_pure, &no_scc);
    }
}
