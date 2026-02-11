fuse_setxattr_resume (fuse_state_t *state)
{
        gf_log ("glusterfs-fuse", GF_LOG_TRACE,
                "%"PRIu64": SETXATTR %s/%"PRIu64" (%s)", state->finh->unique,
                state->loc.path, state->finh->nodeid, state->name);

        FUSE_FOP (state, fuse_setxattr_cbk, GF_FOP_SETXATTR,
                  setxattr, &state->loc, state->dict, state->flags);
}
