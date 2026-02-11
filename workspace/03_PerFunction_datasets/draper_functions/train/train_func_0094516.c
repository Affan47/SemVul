free_state(struct state *state) {
    if (state == NULL)
        return;

    for(int i=0; i < state->exprs_used; i++)
        free_expr(state->exprs[i]);
    free(state->exprs);

    for(int i=0; i < state->value_pool_used; i++)
        release_value(state->value_pool + i);
    free(state->value_pool);
    free(state->values);
    free(state);
}
