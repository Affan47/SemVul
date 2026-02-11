ast_for_for_stmt(struct compiling *c, const node *n)
{
    asdl_seq *_target, *seq = NULL, *suite_seq;
    expr_ty expression;
    expr_ty target, first;
    const node *node_target;

    REQ(n, for_stmt);

    if (NCH(n) == 9) {
        seq = ast_for_suite(c, CHILD(n, 8));
        if (!seq)
            return NULL;
    }

    node_target = CHILD(n, 1);
    _target = ast_for_exprlist(c, node_target, Store);
    if (!_target)
        return NULL;


    first = (expr_ty)asdl_seq_GET(_target, 0);
    if (NCH(node_target) == 1)
        target = first;
    else
        target = Tuple(_target, Store, first->lineno, first->col_offset, c->c_arena);

    expression = ast_for_testlist(c, CHILD(n, 3));
    if (!expression)
        return NULL;
    suite_seq = ast_for_suite(c, CHILD(n, 5));
    if (!suite_seq)
        return NULL;

    return For(target, expression, suite_seq, seq, LINENO(n), n->n_col_offset,
               c->c_arena);
}
