av_random_init(AVRandomState *state, unsigned int seed)
{
    int index;


    state->mt[0] = seed & 0xffffffff;
    for (index = 1; index < AV_RANDOM_N; index++) {
        unsigned int prev= state->mt[index - 1];
        state->mt[index] = (1812433253UL * (prev ^ (prev>>30)) + index) & 0xffffffff;
    }
    state->index= index;
}
