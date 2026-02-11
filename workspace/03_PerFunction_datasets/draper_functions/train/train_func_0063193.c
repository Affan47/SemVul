eval_quick(state_t *state)
{
    int ret;

#ifdef USE_HASH_EVAL
    if (hash_get_eval(state->zobrist, &ret))
        return ret;
#endif

    ret = eval_material(state, WHITE) - eval_material(state, BLACK);
    return state->turn == WHITE ? ret : -ret;
}
