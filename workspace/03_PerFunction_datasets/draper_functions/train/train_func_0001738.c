skipColon(lex_state_t * state) {
    if (!iseos(state) && ischr(state, ':')) {
        state->pos++;
        return SKIP_OK;
    } else {
        return SKIP_NONE;
    }
}
