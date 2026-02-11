zsetcachedevice2(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;
    double wbox[10];
    gs_text_enum_t *penum = op_show_find(i_ctx_p);
    int code = num_params(op, 10, wbox);

    if (penum == 0)
        return_error(e_undefined);
    if (code < 0)
        return code;
    if (zchar_show_width_only(penum))
        return op_show_return_width(i_ctx_p, 10,
                                    (gs_rootfont(igs)->WMode ?
                                     &wbox[6] : &wbox[0]));
    code = gs_text_setcachedevice2(penum, wbox);
    if (code < 0)
        return code;
    pop(10);
    if (code == 1)
        clear_pagedevice(istate);
    return 0;
}
