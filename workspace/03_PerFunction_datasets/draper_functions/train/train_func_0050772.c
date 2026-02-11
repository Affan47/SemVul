pdf14_fill_path(gx_device *dev,	const gs_imager_state *pis,
                           gx_path *ppath, const gx_fill_params *params,
                           const gx_drawing_color *pdcolor,
                           const gx_clip_path *pcpath)
{
    gs_imager_state new_is = *pis;
    int code;
    gs_pattern2_instance_t *pinst = NULL;

    if (pdcolor != NULL && gx_dc_is_pattern1_color(pdcolor)){
        if( gx_pattern1_get_transptr(pdcolor) != NULL ||
            gx_pattern1_clist_has_trans(pdcolor) ){


#if RAW_DUMP


            if (gx_pattern1_get_transptr(pdcolor) != NULL) {
                pdf14_device * ppatdev14 =
                                pdcolor->colors.pattern.p_tile->ttrans->pdev14;
                if (ppatdev14 != NULL) {
                    byte *buf_ptr = ppatdev14->ctx->stack->data  +
                        ppatdev14->ctx->stack->rect.p.y *
                        ppatdev14->ctx->stack->rowstride +
                        ppatdev14->ctx->stack->rect.p.x;
                    dump_raw_buffer(ppatdev14->ctx->stack->rect.q.y -
                                    ppatdev14->ctx->stack->rect.p.y,
                                    ppatdev14->ctx->stack->rect.q.x -
                                    ppatdev14->ctx->stack->rect.p.x,
                                    ppatdev14->ctx->stack->n_planes,
                                    ppatdev14->ctx->stack->planestride,
                                    ppatdev14->ctx->stack->rowstride,
                                    "Pattern_Fill",buf_ptr);
                    global_index++;
                } else {
                     gx_pattern_trans_t *patt_trans =
                                        pdcolor->colors.pattern.p_tile->ttrans;
                     dump_raw_buffer(patt_trans->rect.q.y-patt_trans->rect.p.y,
                                patt_trans->rect.q.x-patt_trans->rect.p.x,
                                                patt_trans->n_chan,
                                patt_trans->planestride, patt_trans->rowstride,
                                "Pattern_Fill_clist", patt_trans->transbytes +
                                patt_trans->rect.p.y * patt_trans->rowstride +
                                patt_trans->rect.p.x);
                    global_index++;
                }
            }
#endif
            code = pdf14_tile_pattern_fill(dev, &new_is, ppath,
                params, pdcolor, pcpath);
            new_is.trans_device = NULL;
            new_is.has_transparency = false;
            return code;
        }
    }
    if (pdcolor != NULL && gx_dc_is_pattern2_color(pdcolor)) {
        pinst =
            (gs_pattern2_instance_t *)pdcolor->ccolor.pattern;
           pinst->saved->has_transparency = true;


           pinst->saved->trans_device = dev;
    }
    update_lop_for_pdf14(&new_is, pdcolor);
    pdf14_set_marking_params(dev, pis);
    new_is.trans_device = dev;
    new_is.has_transparency = true;
    code = gx_default_fill_path(dev, &new_is, ppath, params, pdcolor, pcpath);
    new_is.trans_device = NULL;
    new_is.has_transparency = false;
    if (pinst != NULL){
        pinst->saved->trans_device = NULL;
    }
    return code;
}
