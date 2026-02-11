fuse_readlink (xlator_t *this, fuse_in_header_t *finh, void *msg)
{
        fuse_state_t *state = NULL;
        int32_t       ret = -1;

        GET_STATE (this, finh, state);
        ret = fuse_loc_fill (&state->loc, state, finh->nodeid, 0, NULL);
        if ((state->loc.inode == NULL) ||
            (ret < 0)) {
                gf_log ("glusterfs-fuse", GF_LOG_WARNING,
                        "%"PRIu64" READLINK %s (fuse_loc_fill() returned NULL inode)",
                        finh->unique, state->loc.path);
                send_fuse_err (this, finh, ENOENT);
                free_fuse_state (state);
                return;
        }

        uuid_copy (state->resolve.gfid, state->loc.inode->gfid);
        state->resolve.path = gf_strdup (state->loc.path);

        fuse_resolve_and_resume (state, fuse_readlink_resume);

        return;
}
