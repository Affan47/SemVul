gz_avail(state)
    gz_statep state;
{
    z_streamp strm = &(state->strm);

    if (state->err != Z_OK)
        return -1;
    if (state->eof == 0) {
        if (gz_load(state, state->in, state->size,
                (unsigned *)&(strm->avail_in)) == -1)
            return -1;
        strm->next_in = state->in;
    }
    return 0;
}
