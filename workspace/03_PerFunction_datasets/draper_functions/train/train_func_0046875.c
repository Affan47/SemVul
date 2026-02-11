fuse_do_truncate (fuse_state_t *state, size_t size)
{
        if (state->fd) {
                FUSE_FOP (state, fuse_truncate_cbk, GF_FOP_FTRUNCATE,
                          ftruncate, state->fd, size);
        } else {
                FUSE_FOP (state, fuse_truncate_cbk, GF_FOP_TRUNCATE,
                          truncate, &state->loc, size);
        }

        return;
}
