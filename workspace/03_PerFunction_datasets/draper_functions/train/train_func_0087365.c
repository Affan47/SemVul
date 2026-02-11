fuse_resolve_gfid (fuse_state_t *state)
{
        fuse_resolve_t *resolve  = NULL;
        loc_t          *resolve_loc = NULL;
        int             ret      = 0;

        resolve = state->resolve_now;
        resolve_loc = &resolve->resolve_loc;

        if (!uuid_is_null (resolve->pargfid)) {
                uuid_copy (resolve_loc->gfid, resolve->pargfid);
        } else if (!uuid_is_null (resolve->gfid)) {
                uuid_copy (resolve_loc->gfid, resolve->gfid);
        }

	resolve_loc->inode = inode_new (state->itable);
	ret = inode_path (resolve_loc->inode, NULL,
			  (char **)&resolve_loc->path);

        if (ret <= 0) {
                gf_log (THIS->name, GF_LOG_WARNING,
                        "failed to get the path from inode %s",
                        uuid_utoa (resolve->gfid));
        }

        FUSE_FOP (state, fuse_resolve_gfid_cbk, GF_FOP_LOOKUP,
                  lookup, resolve_loc, NULL);

        return 0;
}
