parse_function_call(struct state *state) {
    const struct func *func = NULL;
    struct expr *expr = NULL;
    int nargs = 0, find = 0;

    for (; find < ARRAY_CARDINALITY(builtin_funcs); find++) {
        if (looking_at(state, builtin_funcs[find].name, "(")) {
            func = builtin_funcs + find;
            break;
        }
    }
    if (func == NULL) {
        STATE_ERROR(state, PATHX_ENAME);
        return;
    }

    if (! match(state, ')')) {
        do {
            nargs += 1;
            parse_expr(state);
            RET_ON_ERROR;
        } while (match(state, ','));

        if (! match(state, ')')) {
            STATE_ERROR(state, PATHX_EPAREN);
            return;
        }
    }

    int found = 0;
    for (int i=find; i < ARRAY_CARDINALITY(builtin_funcs); i++) {
        if (STRNEQ(func->name, builtin_funcs[i].name))
            break;
        if (builtin_funcs[i].arity == nargs) {
            func = builtin_funcs + i;
            found = 1;
            break;
        }
    }

    if (! found) {
        STATE_ERROR(state, PATHX_EARITY);
        return;
    }

    if (ALLOC(expr) < 0) {
        STATE_ENOMEM;
        return;
    }
    expr->tag = E_APP;
    if (ALLOC_N(expr->args, nargs) < 0) {
        free_expr(expr);
        STATE_ENOMEM;
        return;
    }
    expr->func = func;
    for (int i = nargs - 1; i >= 0; i--)
        expr->args[i] = pop_expr(state);

    push_expr(expr, state);
}
