zsetoverprint(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;

    check_type(*op, t_boolean);
    gs_setoverprint(igs, op->value.boolval);
    pop(1);
    return 0;
}
