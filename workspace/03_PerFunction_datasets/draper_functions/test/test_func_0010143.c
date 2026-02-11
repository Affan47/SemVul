compiler_boolop(struct compiler *c, expr_ty e)
{
    basicblock *end;
    int jumpi;
    Py_ssize_t i, n;
    asdl_seq *s;

    assert(e->kind == BoolOp_kind);
    if (e->v.BoolOp.op == And)
        jumpi = JUMP_IF_FALSE_OR_POP;
    else
        jumpi = JUMP_IF_TRUE_OR_POP;
    end = compiler_new_block(c);
    if (end == NULL)
        return 0;
    s = e->v.BoolOp.values;
    n = asdl_seq_LEN(s) - 1;
    assert(n >= 0);
    for (i = 0; i < n; ++i) {
        VISIT(c, expr, (expr_ty)asdl_seq_GET(s, i));
        ADDOP_JABS(c, jumpi, end);
    }
    VISIT(c, expr, (expr_ty)asdl_seq_GET(s, n));
    compiler_use_next_block(c, end);
    return 1;
}
