dca_dynrng (dca_state_t * state,
                 level_t (* call) (level_t, void *), void * data)
{
    state->dynrange = 0;
    if (call) {
        state->dynrange = 1;
        state->dynrngcall = call;
        state->dynrngdata = data;
    }
}
