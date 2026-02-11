set_screen_continue(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;
    double value;
    int code = real_param(op, &value);

    if (code < 0)
        return code;
    code = gs_screen_next(senum, value);
    if (code < 0)
        return code;
    pop(1);
    return screen_sample(i_ctx_p);
}
