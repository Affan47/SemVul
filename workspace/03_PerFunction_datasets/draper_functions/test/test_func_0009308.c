c_param_request(gs_param_list * plist, gs_param_name pkey)
{
    gs_c_param_list *const cplist = (gs_c_param_list *)plist;
    gs_c_param *pparam;

    cplist->any_requested = true;
    if (c_param_find(cplist, pkey, true))
        return 0;
    pparam = c_param_add(cplist, pkey);
    if (pparam == 0)
        return_error(gs_error_VMerror);
    pparam->type = gs_param_type_any;
    cplist->head = pparam;
    return 0;
}
