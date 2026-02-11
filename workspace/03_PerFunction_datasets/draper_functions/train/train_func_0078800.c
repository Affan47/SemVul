zpop(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;

    check_op(1);
    pop(1);
    return 0;
}
