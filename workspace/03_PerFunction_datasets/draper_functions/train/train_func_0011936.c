compiler_ifexp(struct compiler *c, expr_ty e)
{
    basicblock *end, *next;

    assert(e->kind == IfExp_kind);
    end = compiler_new_block(c);
    if (end == NULL)
        return 0;
    next = compiler_new_block(c);
    if (next == NULL)
        return 0;
    VISIT(c, expr, e->v.IfExp.test);
    ADDOP_JABS(c, POP_JUMP_IF_FALSE, next);
    VISIT(c, expr, e->v.IfExp.body);
    ADDOP_JREL(c, JUMP_FORWARD, end);
    compiler_use_next_block(c, next);
    VISIT(c, expr, e->v.IfExp.orelse);
    compiler_use_next_block(c, end);
    return 1;
}
