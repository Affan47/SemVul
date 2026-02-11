get_key(struct lens *lens, struct state *state) {
    ensure0(lens->tag == L_KEY, state->info);
    if (! REG_MATCHED(state))
        no_match_error(state, lens);
    else {
        state->key = token(state);
        if (state->span) {
            state->span->label_start = REG_START(state);
            state->span->label_end = REG_END(state);
            update_span(state->span, REG_START(state), REG_END(state));
        }
    }
    return NULL;
}
