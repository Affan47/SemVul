font_param(const ref * pfdict, gs_font ** ppfont)
{


    ref *pid;
    gs_font *pfont;
    const font_data *pdata;

    check_type(*pfdict, t_dictionary);
    if (dict_find_string(pfdict, "FID", &pid) <= 0 ||
        !r_has_type(pid, t_fontID)
        )
        return_error(e_invalidfont);
    pfont = r_ptr(pid, gs_font);
    if (pfont == 0)
        return_error(e_invalidfont);
    pdata = pfont->client_data;
    if (!obj_eq(pfont->memory, &pdata->dict, pfdict))
        return_error(e_invalidfont);
    *ppfont = pfont;
    return 0;
}
