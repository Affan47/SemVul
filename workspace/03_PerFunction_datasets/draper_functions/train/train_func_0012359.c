fuse_readdir (xlator_t *this, fuse_in_header_t *finh, void *msg)
{
        struct fuse_read_in *fri = msg;

        fuse_state_t *state = NULL;
        fd_t         *fd = NULL;

        GET_STATE (this, finh, state);
        state->size = fri->size;
        state->off = fri->offset;
        fd = FH_TO_FD (fri->fh);
        state->fd = fd;

        fuse_resolve_fd_init (state, &state->resolve, fd);

        fuse_resolve_and_resume (state, fuse_readdir_resume);
}
