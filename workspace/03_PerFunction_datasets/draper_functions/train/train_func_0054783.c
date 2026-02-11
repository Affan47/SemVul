parse_number(struct state *state) {
    struct expr *expr = NULL;
    unsigned long val;
    char *end;

    errno = 0;
    val = strtoul(state->pos, &end, 10);
    if (errno || end == state->pos || (int) val != val) {
        STATE_ERROR(state, PATHX_ENUMBER);
        return;
    }

    state->pos = end;

    if (ALLOC(expr) < 0)
        goto err_nomem;
    expr->tag = E_VALUE;
    expr->value_ind = make_value(T_NUMBER, state);
    if (HAS_ERROR(state))
        goto error;
    expr_value(expr, state)->number = val;

    push_expr(expr, state);
    return;

 err_nomem:
    STATE_ENOMEM;
 error:
    free_expr(expr);
    return;
}
