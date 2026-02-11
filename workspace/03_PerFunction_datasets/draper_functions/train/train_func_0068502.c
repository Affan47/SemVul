gs_end_transparency_mask(gs_state *pgs,
                         gs_transparency_channel_selector_t csel)
{
    gs_pdf14trans_params_t params = { 0 };
    gs_pdf14trans_params_t params_color = { 0 };
    gs_imager_state * pis = (gs_imager_state *)pgs;
    int code;

    if (check_for_nontrans_pattern(pgs,
                  (unsigned char *)"gs_end_transparency_mask")) {
        return(0);
    }


    pis->trans_flags.xstate_change = true;
    if_debug1m('v', pis->memory,
               "[v]xstate_changed set true, gstate level is %d\n", pgs->level);
    if_debug2m('v', pis->memory,
               "[v](0x%lx)gs_end_transparency_mask(%d)\n", (ulong)pgs,
               (int)csel);
    params.pdf14_op = PDF14_END_TRANS_MASK;
    params.csel = csel;

    if_debug0m('v', pis->memory, "[v]popping soft mask color sending\n");
    params_color.pdf14_op = PDF14_POP_SMASK_COLOR;
    code = gs_state_update_pdf14trans(pgs, &params_color);
    if (code < 0)
        return(code);
    return gs_state_update_pdf14trans(pgs, &params);
}
