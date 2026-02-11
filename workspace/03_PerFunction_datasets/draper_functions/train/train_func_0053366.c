zround(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;

    switch (r_type(op)) {
        default:
            return_op_typecheck(op);
        case t_real:
            op->value.realval = floor(op->value.realval + 0.5);
        case t_integer:;
    }
    return 0;
}
