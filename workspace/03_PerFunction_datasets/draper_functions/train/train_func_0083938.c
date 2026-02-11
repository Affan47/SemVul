skipQuoteProgramData(lex_state_t * state, int quote) {
    while (!iseos(state)) {
        if (isascii7bit(state->pos[0]) && !ischr(state, quote)) {
            state->pos++;
        } else if (ischr(state, quote)) {
            state->pos++;
            if (!iseos(state) && ischr(state, quote)) {
                state->pos++;
            } else {
                state->pos--;
                break;
            }
        }
    }
}
