zwritecvp_continue(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;

    check_type(*op, t_integer);
    if (op->value.intval != (uint) op->value.intval)
        return_error(e_rangecheck);
    return zwritecvp_at(i_ctx_p, op - 1, (uint) op->value.intval, false);
}
