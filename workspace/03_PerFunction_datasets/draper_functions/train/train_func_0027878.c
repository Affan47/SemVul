gstate_copy(gs_state * pto, const gs_state * pfrom,
            gs_state_copy_reason_t reason, client_name_t cname)
{
    gs_state_parts parts;

    GSTATE_ASSIGN_PARTS(&parts, pto);

    if (pfrom->line_params.dash.pattern || pto->line_params.dash.pattern) {
        int code = gstate_copy_dash(pto, pfrom);

        if (code < 0)
            return code;
    }


    cs_adjust_counts_icc(pto, -1);
    gs_swapcolors_quick(pto);
    cs_adjust_counts_icc(pto, -1);
    gs_swapcolors_quick(pto);
    gx_path_assign_preserve(pto->path, pfrom->path);
    gx_cpath_assign_preserve(pto->clip_path, pfrom->clip_path);


    if (pfrom->effective_clip_shared) {


        parts.effective_clip_path =
            (pfrom->effective_clip_path == pfrom->view_clip ?
             pto->view_clip : parts.clip_path);
    } else
        gx_cpath_assign_preserve(pto->effective_clip_path,
                                 pfrom->effective_clip_path);
    *parts.color[0].ccolor    = *pfrom->color[0].ccolor;
    *parts.color[0].dev_color = *pfrom->color[0].dev_color;
    *parts.color[1].ccolor    = *pfrom->color[1].ccolor;
    *parts.color[1].dev_color = *pfrom->color[1].dev_color;

    rc_pre_assign(pto->device, pfrom->device, cname);
    rc_pre_assign(pto->dfilter_stack, pfrom->dfilter_stack, cname);
    if (pto->clip_stack != pfrom->clip_stack) {
        clip_stack_rc_adjust(pfrom->clip_stack, 1, cname);
        clip_stack_rc_adjust(pto->clip_stack, -1, cname);
    }
    {
        struct gx_pattern_cache_s *pcache = pto->pattern_cache;
        void *pdata = pto->client_data;
        gs_memory_t *mem = pto->memory;
        gs_state *saved = pto->saved;
        float *pattern = pto->line_params.dash.pattern;

        gs_imager_state_pre_assign((gs_imager_state *)pto,
                                   (const gs_imager_state *)pfrom);
        *pto = *pfrom;
        pto->client_data = pdata;
        pto->memory = mem;
        pto->saved = saved;
        pto->line_params.dash.pattern = pattern;
        if (pto->pattern_cache == 0)
            pto->pattern_cache = pcache;
        if (pfrom->client_data != 0) {

            gstate_copy_client_data((gs_state *) pfrom, pdata,
                                    pfrom->client_data, reason);
        }
    }
    GSTATE_ASSIGN_PARTS(pto, &parts);
    cs_adjust_counts_icc(pto, 1);
    gs_swapcolors_quick(pto);
    cs_adjust_counts_icc(pto, 1);
    gs_swapcolors_quick(pto);
    pto->show_gstate =
        (pfrom->show_gstate == pfrom ? pto : 0);
    return 0;
}
