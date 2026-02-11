gs_shading_Cp_fill_rectangle(const gs_shading_t * psh0, const gs_rect * rect,
                             const gs_fixed_rect * rect_clip,
                             gx_device * dev, gs_imager_state * pis)
{
    const gs_shading_Cp_t * const psh = (const gs_shading_Cp_t *)psh0;
    patch_fill_state_t state;
    shade_coord_stream_t cs;
    patch_curve_t curve[4];
    int code;

    code = mesh_init_fill_state((mesh_fill_state_t *) &state,
                         (const gs_shading_mesh_t *)psh0, rect_clip, dev, pis);
    if (code < 0) {
        if (state.icclink != NULL) gsicc_release_link(state.icclink);
        return code;
    }
    state.Function = psh->params.Function;
    code = init_patch_fill_state(&state);
    if(code < 0) {
        if (state.icclink != NULL) gsicc_release_link(state.icclink);
        return code;
    }
    if (VD_TRACE_TENSOR_PATCH && vd_allowed('s')) {
        vd_get_dc('s');
        vd_set_shift(0, 0);
        vd_set_scale(0.01);
        vd_set_origin(0, 0);

    }

    curve[0].straight = curve[1].straight = curve[2].straight = curve[3].straight = false;
    shade_next_init(&cs, (const gs_shading_mesh_params_t *)&psh->params, pis);
    while ((code = shade_next_patch(&cs, psh->params.BitsPerFlag,
                                    curve, NULL)) == 0 &&
           (code = patch_fill(&state, curve, NULL, Cp_transform)) >= 0
        ) {
        DO_NOTHING;
    }
    if (VD_TRACE_TENSOR_PATCH && vd_allowed('s'))
        vd_release_dc;
    if (term_patch_fill_state(&state))
        return_error(gs_error_unregistered);
    if (state.icclink != NULL) gsicc_release_link(state.icclink);
    return min(code, 0);
}
