fuse_readlink_resume (fuse_state_t *state)
{
        if (!state->loc.inode) {
                gf_log ("glusterfs-fuse", GF_LOG_ERROR,
                        "READLINK %"PRIu64" (%s) resolution failed",
                        state->finh->unique, uuid_utoa (state->resolve.gfid));
                send_fuse_err (state->this, state->finh, ENOENT);
                free_fuse_state (state);
                return;
        }

        gf_log ("glusterfs-fuse", GF_LOG_TRACE,
                "%"PRIu64" READLINK %s/%s", state->finh->unique,
                state->loc.path, uuid_utoa (state->loc.inode->gfid));

        FUSE_FOP (state, fuse_readlink_cbk, GF_FOP_READLINK,
                  readlink, &state->loc, 4096, state->xdata);
}
