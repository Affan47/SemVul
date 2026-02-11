scpiLex_SuffixProgramData(lex_state_t * state, scpi_token_t * token) {
    token->ptr = state->pos;

    skipChr(state, '/');


    if (skipAlpha(state)) {
        skipChr(state, '-');
        skipDigit(state);

        while (skipSlashDot(state)) {
            skipAlpha(state);
            skipChr(state, '-');
            skipDigit(state);
        }
    }

    token->len = state->pos - token->ptr;
    if ((token->len > 0)) {
        token->type = SCPI_TOKEN_SUFFIX_PROGRAM_DATA;
    } else {
        token->type = SCPI_TOKEN_UNKNOWN;
        state->pos = token->ptr;
        token->len = 0;
    }

    return token->len;
}
