gx_dc_binary_masked_fill_rect(const gx_device_color * pdevc,
                              int x, int y, int w, int h, gx_device * dev,
                              gs_logical_operation_t lop,
                              const gx_rop_source_t * source)
{
    gx_color_tile *ptile = pdevc->mask.m_tile;
    tile_fill_state_t state;
    int code;

    code = tile_fill_init(&state, pdevc, dev, true);
    if (code < 0)
        return code;
    if (state.pcdev == dev || ptile->is_simple)
        code = (*gx_dc_type_data_ht_binary.fill_rectangle)
            (pdevc, x, y, w, h, state.pcdev, lop, source);
    else {
        state.lop = lop;
        state.source = source;
        state.fill_rectangle = gx_dc_type_data_ht_binary.fill_rectangle;
        code = tile_by_steps(&state, x, y, w, h, ptile, &ptile->tmask,
                             tile_masked_fill);
    }
    if (CLIPDEV_INSTALLED) {
        tile_clip_free((gx_device_tile_clip *)state.cdev);
        state.cdev = NULL;
    }
    return code;
}
