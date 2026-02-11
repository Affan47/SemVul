s_DCTE_get_params(gs_param_list * plist, const stream_DCT_state * ss, bool all)
{
    gs_memory_t *mem = ss->memory;
    stream_DCT_state dcts_defaults;
    const stream_DCT_state *defaults = 0;
    dcte_scalars_t params;
    const jpeg_compress_data *jcdp = ss->data.compress;
    int code;

    if (!all) {
        jpeg_compress_data *jcdp_default = gs_alloc_struct_immovable(mem,
           jpeg_compress_data, &st_jpeg_compress_data, "s_DCTE_get_params");
        if (jcdp_default == 0)
            return_error(gs_error_VMerror);
        defaults = &dcts_defaults;
        (*s_DCTE_template.set_defaults) ((stream_state *) & dcts_defaults);
        dcts_defaults.data.compress = jcdp_default;
        jcdp_default->memory = dcts_defaults.jpeg_memory = mem;
        if ((code = gs_jpeg_create_compress(&dcts_defaults)) < 0)
            goto fail;

        dcts_defaults.data.common->Picky = 0;
        dcts_defaults.data.common->Relax = 0;
    }
    params.Columns = jcdp->cinfo.image_width;
    params.Rows = jcdp->cinfo.image_height;
    params.Colors = jcdp->cinfo.input_components;
    params.Markers.data = ss->Markers.data;
    params.Markers.size = ss->Markers.size;
    params.Markers.persistent = false;
    params.NoMarker = ss->NoMarker;
    params.Resync = jcdp->cinfo.restart_interval;

    if ((code = s_DCT_get_params(plist, ss, defaults)) < 0 ||
        (code = gs_param_write_items(plist, &params,
                                     &dcte_scalars_default,
                                     s_DCTE_param_items)) < 0 ||
        (code = dcte_get_samples(plist, "HSamples", params.Colors,
                                 jcdp, mem, false, all)) < 0 ||
        (code = dcte_get_samples(plist, "VSamples", params.Colors,
                                 jcdp, mem, true, all)) < 0 ||
    (code = s_DCT_get_quantization_tables(plist, ss, defaults, true)) < 0 ||
        (code = s_DCT_get_huffman_tables(plist, ss, defaults, true)) < 0
        )
        DO_NOTHING;

  fail:if (defaults) {
        gs_jpeg_destroy(&dcts_defaults);
        gs_free_object(mem, dcts_defaults.data.compress,
                       "s_DCTE_get_params");
    }
    return code;
}
