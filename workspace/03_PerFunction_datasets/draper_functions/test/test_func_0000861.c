zinvertmatrix(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;
    gs_matrix m;
    int code;

    if ((code = read_matrix(imemory, op - 1, &m)) < 0 ||
        (code = gs_matrix_invert(&m, &m)) < 0 ||
        (code = write_matrix(op, &m)) < 0
        )
        return code;
    op[-1] = *op;
    pop(1);
    return code;
}
