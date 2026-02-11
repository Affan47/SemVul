zserialnumber(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;

    push(1);
    make_int(op, gp_serialnumber());
    return 0;
}
