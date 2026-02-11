gx_hld_stringwidth_begin(gs_imager_state * pis, gx_path **path)
{
    gs_state *pgs = (gs_state *)pis;
    extern_st(st_gs_state);
    int code;

    if (gs_object_type(pis->memory, pis) != &st_gs_state)
        return_error(gs_error_unregistered);
    code = gs_gsave(pgs);
    if (code < 0)
        return code;
    gs_newpath(pgs);
    *path = pgs->path;
    gx_translate_to_fixed(pgs, fixed_0, fixed_0);
    return gx_path_add_point(pgs->path, fixed_0, fixed_0);
}
