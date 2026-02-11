zcheckpassword(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;
    ref params[2];
    array_param_list list;
    gs_param_list *const plist = (gs_param_list *)&list;
    int result = 0;
    int code = name_ref(imemory, (const byte *)"Password", 8, &params[0], 0);
    password pass;

    if (code < 0)
        return code;
    params[1] = *op;
    array_param_list_read(&list, params, 2, NULL, false, iimemory);
    if (dict_read_password(&pass, systemdict, "StartJobPassword") >= 0 &&
        param_check_password(plist, &pass) == 0
        )
        result = 1;
    if (dict_read_password(&pass, systemdict, "SystemParamsPassword") >= 0 &&
        param_check_password(plist, &pass) == 0
        )
        result = 2;
    iparam_list_release(&list);
    make_int(op, result);
    return 0;
}
