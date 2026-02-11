skipBinNum(lex_state_t * state) {
    int someNumbers = 0;
    while (!iseos(state) && isbdigit(state->pos[0])) {
        state->pos++;
        someNumbers++;
    }
    return someNumbers;
}
