fuse_removexattr (xlator_t *this, fuse_in_header_t *finh, void *msg)

{
        char *name = msg;

        fuse_state_t *state = NULL;
        fuse_private_t *priv = NULL;
        int32_t       ret = -1;
        char *newkey = NULL;

        priv = this->private;

        GET_STATE (this, finh, state);
        ret = fuse_loc_fill (&state->loc, state, finh->nodeid, 0, NULL);
        if ((state->loc.inode == NULL) ||
            (ret < 0)) {
                gf_log ("glusterfs-fuse", GF_LOG_DEBUG,
                        "%"PRIu64": REMOVEXATTR %s/%"PRIu64" (%s) (fuse_loc_fill() failed)",
                        finh->unique, state->loc.path, finh->nodeid, name);

                send_fuse_err (this, finh, ENOENT);
                free_fuse_state (state);
                return;
        }

        ret = fuse_flip_xattr_ns (priv, name, &newkey);
        if (ret) {
                send_fuse_err (this, finh, ENOMEM);
                free_fuse_state (state);
                return;
        }

        state->name = newkey;
        uuid_copy (state->resolve.gfid, state->loc.inode->gfid);
        state->resolve.path = gf_strdup (state->loc.path);

        fuse_resolve_and_resume (state, fuse_removexattr_resume);
        return;
}
