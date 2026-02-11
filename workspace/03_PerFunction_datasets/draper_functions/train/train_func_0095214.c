fuse_unlink_resume (fuse_state_t *state)
{
        if (!state->loc.inode) {
                gf_log ("fuse", GF_LOG_WARNING, "path resolving failed");
                send_fuse_err (state->this, state->finh, ENOENT);
                free_fuse_state (state);
                return;
        }
        gf_log ("glusterfs-fuse", GF_LOG_TRACE,
                "%"PRIu64": UNLINK %s", state->finh->unique,
                state->loc.path);

        FUSE_FOP (state, fuse_unlink_cbk, GF_FOP_UNLINK,
                  unlink, &state->loc);

}
