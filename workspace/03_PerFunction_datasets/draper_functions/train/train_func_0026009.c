psdf_put_image_dict_param(gs_param_list * plist, const gs_param_name pname,
                          gs_c_param_list **pplvalue,
                          const stream_template * templat,
                          ss_put_params_t put_params, gs_memory_t * mem)
{
    gs_param_dict dict;
    gs_c_param_list *plvalue = *pplvalue;
    int code;

    mem = gs_memory_stable(mem);
    switch (code = param_begin_read_dict(plist, pname, &dict, false)) {
        default:
            param_signal_error(plist, pname, code);
            return code;
        case 1:
            return 0;
        case 0: {

            stream_state *ss = s_alloc_state(mem, templat->stype, pname);

            if (ss == 0)
                return_error(gs_error_VMerror);
            ss->templat = templat;
            if (templat->set_defaults)
                templat->set_defaults(ss);
            code = put_params(dict.list, ss);
            if (templat->release)
                templat->release(ss);
            gs_free_object(mem, ss, pname);
            if (code < 0) {
                param_signal_error(plist, pname, code);
            } else {
                plvalue = gs_c_param_list_alloc(mem, pname);
                if (plvalue == 0)
                    return_error(gs_error_VMerror);
                gs_c_param_list_write(plvalue, mem);
                code = param_list_copy((gs_param_list *)plvalue,
                                       dict.list);
                if (code < 0) {
                    gs_c_param_list_release(plvalue);
                    gs_free_object(mem, plvalue, pname);
                    plvalue = *pplvalue;
                }
            }
        }
        param_end_read_dict(plist, pname, &dict);
        break;
    }
    if (plvalue != *pplvalue) {
        if (*pplvalue)
            gs_c_param_list_release(*pplvalue);
        *pplvalue = plvalue;
    }
    return code;
}
