s_DCTD_get_params(gs_param_list * plist, const stream_DCT_state * ss, bool all)
{
    stream_DCT_state dcts_defaults;
    const stream_DCT_state *defaults;

    if (all)
        defaults = 0;
    else {
        (*s_DCTE_template.set_defaults) ((stream_state *) & dcts_defaults);
        defaults = &dcts_defaults;
    }

    return s_DCT_get_params(plist, ss, defaults);
}
