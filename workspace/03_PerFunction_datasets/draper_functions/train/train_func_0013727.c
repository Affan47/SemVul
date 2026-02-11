visit_enter(struct lens *lens,
                        ATTRIBUTE_UNUSED size_t start,
                        ATTRIBUTE_UNUSED size_t end,
                        void *data) {
    struct rec_state *rec_state = data;
    struct state *state = rec_state->state;
    struct ast *child;

    if (state->error != NULL)
        return;

    if (debugging("cf.get"))
        dbg_visit(lens, '{', start, end, rec_state->fused, rec_state->lvl);
    rec_state->lvl += 1;
    if (lens->tag == L_SUBTREE) {

        struct frame *f = push_frame(rec_state, lens);
        f->key = state->key;
        f->value = state->value;
        f->span = state->span;
        state->key = NULL;
        state->value = NULL;
    } else if (lens->tag == L_MAYBE) {
        push_frame(rec_state, lens);
        if (state->info->flags & AUG_ENABLE_SPAN) {
            state->span = make_span(state->info);
            ERR_NOMEM(state->span == NULL, state->info);
        }
    }
    child = ast_append(rec_state, lens, start, end);
    if (child != NULL)
        rec_state->ast = child;
 error:
    return;
}
