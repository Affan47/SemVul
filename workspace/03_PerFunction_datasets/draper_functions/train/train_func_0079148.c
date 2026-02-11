get_subtree(struct lens *lens, struct state *state) {
    char *key = state->key;
    char *value = state->value;
    struct span *span = state->span;

    struct tree *tree = NULL, *children;

    state->key = NULL;
    state->value = NULL;
    if (state->info->flags & AUG_ENABLE_SPAN) {
        state->span = make_span(state->info);
        ERR_NOMEM(state->span == NULL, state->info);
    }

    children = get_lens(lens->child, state);

    tree = make_tree(state->key, state->value, NULL, children);
    tree->span = state->span;

    if (state->span != NULL) {
        update_span(span, state->span->span_start, state->span->span_end);
    }

    state->key = key;
    state->value = value;
    state->span = span;
    return tree;
 error:
    return NULL;
}
