gx_cpath_path_list_new(gs_memory_t *mem, gx_clip_path *pcpath, int rule,
                        gx_path *ppfrom, gx_cpath_path_list *next, gx_cpath_path_list **pnew)
{
    int code;
    client_name_t cname = "gx_cpath_path_list_new";
    gx_cpath_path_list *pcplist = gs_alloc_struct(mem, gx_cpath_path_list,
                                                  &st_cpath_path_list, cname);

    if (pcplist == 0)
        return_error(gs_error_VMerror);
    rc_init_free(pcplist, mem, 1, rc_free_cpath_path_list);
    if (pcpath!=NULL && !pcpath->path_valid) {
        code = gx_path_init_contained_shared(&pcplist->path, NULL, mem, cname);
        if (code < 0)
            return code;
        code = gx_cpath_to_path(pcpath, &pcplist->path);
    } else {
        gx_path_init_local(&pcplist->path, mem);
        code = gx_path_assign_preserve(&pcplist->path, ppfrom);
    }
    if (code < 0)
        return code;
    pcplist->next = next;
    pcplist->rule = rule;
    *pnew = pcplist;
    return 0;
}
