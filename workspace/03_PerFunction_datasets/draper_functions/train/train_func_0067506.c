zsetalpha(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;
    double alpha;
    int code;

    if (real_param(op, &alpha) < 0)
        return_op_typecheck(op);
    if ((code = gs_setalpha(igs, alpha)) < 0)
        return code;
    pop(1);
    return 0;
}
