ns_filter(struct nodeset *ns, struct pred *predicates,
                      struct state *state) {
    if (predicates == NULL)
        return;

    struct tree *old_ctx = state->ctx;
    uint old_ctx_len = state->ctx_len;
    uint old_ctx_pos = state->ctx_pos;

    for (int p=0; p < predicates->nexpr; p++) {
        state->ctx_len = ns->used;
        state->ctx_pos = 1;
        for (int i=0; i < ns->used; state->ctx_pos++) {
            state->ctx = ns->nodes[i];
            bool match = eval_pred(predicates->exprs[p], state);
            RET_ON_ERROR;
            if (match) {
                i+=1;
            } else {
                ns_remove(ns, i);
            }
        }
    }

    state->ctx = old_ctx;
    state->ctx_pos = old_ctx_pos;
    state->ctx_len = old_ctx_len;
}
