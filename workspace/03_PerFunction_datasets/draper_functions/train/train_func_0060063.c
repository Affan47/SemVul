func_label(struct state *state, int nargs) {
    ensure_arity(0, 0);
    value_ind_t vind = make_value(T_STRING, state);
    char *s;

    RET_ON_ERROR;

    if (state->ctx->label)
        s = strdup(state->ctx->label);
    else
        s = strdup("");
    if (s == NULL) {
        STATE_ENOMEM;
        return;
    }
    state->value_pool[vind].string = s;
    push_value(vind, state);
}
