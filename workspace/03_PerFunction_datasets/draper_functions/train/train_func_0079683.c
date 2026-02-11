gx_path_subpath_start_point(const gx_path * ppath, gs_fixed_point * ppt)
{
    const subpath *psub = ppath->current_subpath;

    if (!psub)
        return_error(gs_error_nocurrentpoint);
    *ppt = psub->pt;
    return 0;
}
