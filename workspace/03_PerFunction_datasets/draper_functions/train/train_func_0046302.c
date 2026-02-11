fuse_resolve_continue (fuse_state_t *state)
{
        fuse_resolve_t     *resolve = NULL;
        int                   ret = 0;

        resolve = state->resolve_now;

        resolve->op_ret   = 0;
        resolve->op_errno = 0;


        if (!uuid_is_null (resolve->pargfid))
                ret = fuse_resolve_entry_simple (state);
        else if (!uuid_is_null (resolve->gfid))
                ret = fuse_resolve_inode_simple (state);
        if (ret)
                gf_log (THIS->name, GF_LOG_DEBUG,
                        "return value of resolve_*_simple %d", ret);

        fuse_resolve_loc_touchup (state);

        fuse_resolve_all (state);

        return 0;
}
