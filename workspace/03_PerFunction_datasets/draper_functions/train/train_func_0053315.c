ast_for_funcdef(struct compiling *c, const node *n, asdl_seq *decorator_seq)
{

    identifier name;
    arguments_ty args;
    asdl_seq *body;
    expr_ty returns = NULL;
    int name_i = 1;

    REQ(n, funcdef);

    name = NEW_IDENTIFIER(CHILD(n, name_i));
    if (!name)
        return NULL;
    if (forbidden_name(name, CHILD(n, name_i), 0))
        return NULL;
    args = ast_for_arguments(c, CHILD(n, name_i + 1));
    if (!args)
        return NULL;
    if (TYPE(CHILD(n, name_i+2)) == RARROW) {
        returns = ast_for_expr(c, CHILD(n, name_i + 3));
        if (!returns)
            return NULL;
        name_i += 2;
    }
    body = ast_for_suite(c, CHILD(n, name_i + 3));
    if (!body)
        return NULL;

    return FunctionDef(name, args, body, decorator_seq, returns, LINENO(n),
                       n->n_col_offset, c->c_arena);
}
