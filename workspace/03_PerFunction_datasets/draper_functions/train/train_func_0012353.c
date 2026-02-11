fuse_resolve_new_fd (fuse_state_t *state)
{
        fuse_resolve_t *resolve = NULL;
        fd_t         *new_fd  = NULL;
        fd_t         *fd      = NULL;

        resolve = state->resolve_now;
        fd = resolve->fd;

        new_fd = fd_create (state->loc.inode, state->finh->pid);
        new_fd->flags = (fd->flags & ~O_TRUNC);

        gf_log ("resolve", GF_LOG_DEBUG,
                "%"PRIu64": OPEN %s", state->finh->unique,
                state->loc.path);

        FUSE_FOP (state, fuse_resolve_newfd_cbk, GF_FOP_OPEN,
                  open, &state->loc, new_fd->flags, new_fd, 0);
}
