ztruncate(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;

    switch (r_type(op)) {
        default:
            return_op_typecheck(op);
        case t_real:
            op->value.realval =
                (op->value.realval < 0.0 ?
                 ceil(op->value.realval) :
                 floor(op->value.realval));
        case t_integer:;
    }
    return 0;
}
