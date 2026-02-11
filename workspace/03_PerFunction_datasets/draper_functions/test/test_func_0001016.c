fuse_rmdir_resume (fuse_state_t *state)
{
        if (!state->loc.parent || !state->loc.inode) {
                gf_log ("glusterfs-fuse", GF_LOG_ERROR,
                        "RMDIR %"PRId64" (%s/%s) resolution failed",
                        state->finh->nodeid, uuid_utoa (state->resolve.gfid),
                        state->resolve.bname);
                send_fuse_err (state->this, state->finh, ENOENT);
                free_fuse_state (state);
                return;
        }

        gf_log ("glusterfs-fuse", GF_LOG_TRACE,
                "%"PRIu64": RMDIR %s", state->finh->unique,
                state->loc.path);

        FUSE_FOP (state, fuse_unlink_cbk, GF_FOP_RMDIR,
                  rmdir, &state->loc, 0, state->xdata);
}
