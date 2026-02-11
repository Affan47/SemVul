option_matchdone(state)
    option_state *state;
{
    if (state->buf) free(state->buf);
    if (state->gkv) sdb_freematch(state->gkv, state->gtotal, 1);
    if (state->ukv) sdb_freematch(state->ukv, state->utotal, 0);
    state->buf = NULL;
    state->gkv = state->ukv = NULL;
}
