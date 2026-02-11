zbitadd(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;

    check_type(*op, t_integer);
    check_type(op[-1], t_integer);
    op[-1].value.intval += op->value.intval;
    pop(1);
    return 0;
}
