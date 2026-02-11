fuse_mknod (xlator_t *this, fuse_in_header_t *finh, void *msg)
{
        struct fuse_mknod_in *fmi = msg;
        char         *name = (char *)(fmi + 1);

        fuse_state_t   *state = NULL;
        fuse_private_t *priv = NULL;
        int32_t         ret = -1;

        priv = this->private;
#if FUSE_KERNEL_MINOR_VERSION >= 12
        if (priv->proto_minor < 12)
                name = (char *)msg + FUSE_COMPAT_MKNOD_IN_SIZE;
#endif

        GET_STATE (this, finh, state);

        uuid_generate (state->gfid);

        fuse_resolve_entry_init (state, &state->resolve, finh->nodeid, name);

        state->mode = fmi->mode;
        state->rdev = fmi->rdev;

        priv = this->private;
#if FUSE_KERNEL_MINOR_VERSION >=12
        FUSE_ENTRY_CREATE(this, priv, finh, state, fmi, "MKNOD");
#endif

        fuse_resolve_and_resume (state, fuse_mknod_resume);

        return;
}
