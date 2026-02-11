gs_setcolorspace(gs_state * pgs, gs_color_space * pcs)
{
    int             code = 0;

    code = gs_setcolorspace_only(pgs, pcs);
    if (code >= 0) {
        pgs->color[0].color_space->pclient_color_space_data =
            pcs->pclient_color_space_data;
        cs_full_init_color(pgs->color[0].ccolor, pcs);
        gx_unset_dev_color(pgs);
    }
    return code;
}
