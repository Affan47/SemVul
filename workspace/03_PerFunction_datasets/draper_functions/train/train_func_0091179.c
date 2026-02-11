cie_exec_tpqr(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;
    const ref *ppt = op[-1].value.const_refs;
    uint space = r_space(op - 1);
    int i;

    check_op(3);
    push(4);
    *op = op[-4];
    op[-1] = op[-6];
    for (i = 0; i < 4; i++)
        make_const_array(op - 5 + i, a_readonly | space,
                         6, ppt + i * 6);
    make_mark(op - 6);
    return zexec(i_ctx_p);
}
