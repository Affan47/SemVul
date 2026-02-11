traverse_cb(hid_t loc_id, const char *path, const H5L_info_t *linfo,
    void *_udata)
{
    trav_ud_traverse_t *udata = (trav_ud_traverse_t *)_udata;
    char *new_name = NULL;
    const char *full_name;
    const char *already_visited = NULL;


    if(udata->is_absolute) {
        size_t base_len = HDstrlen(udata->base_grp_name);
        size_t add_slash = base_len ? ((udata->base_grp_name)[base_len-1] != '/') : 1;

        if(NULL == (new_name = (char*)HDmalloc(base_len + add_slash + HDstrlen(path) + 1)))
            return(H5_ITER_ERROR);
        HDstrcpy(new_name, udata->base_grp_name);
        if (add_slash)
            new_name[base_len] = '/';
        HDstrcpy(new_name + base_len + add_slash, path);
        full_name = new_name;
    }
    else
        full_name = path;


    if(linfo->type == H5L_TYPE_HARD) {
        H5O_info_t oinfo;


        if(H5Oget_info_by_name(loc_id, path, &oinfo, H5P_DEFAULT) < 0) {
            if(new_name)
                HDfree(new_name);
            return(H5_ITER_ERROR);
        }


        if(oinfo.rc > 1)
            if(NULL == (already_visited = trav_addr_visited(udata->seen, oinfo.addr)))
                trav_addr_add(udata->seen, oinfo.addr, full_name);


        if(udata->visitor->visit_obj)
            if((*udata->visitor->visit_obj)(full_name, &oinfo, already_visited, udata->visitor->udata) < 0) {
                if(new_name)
                    HDfree(new_name);
                return(H5_ITER_ERROR);
            }
    }
    else {

        if(udata->visitor->visit_lnk)
            if((*udata->visitor->visit_lnk)(full_name, linfo, udata->visitor->udata) < 0) {
                if(new_name)
                    HDfree(new_name);
                return(H5_ITER_ERROR);
            }
    }

    if(new_name)
        HDfree(new_name);

    return(H5_ITER_CONT);
}
