find_by_seq(struct connection_walk_state *state,
            uint8_t seq)
{
    unsigned i;

    for (i = 0; i < state->queue_size; i++)
        if (state->queue[i].seq == seq)
            return &state->queue[i];

    return NULL;
}
