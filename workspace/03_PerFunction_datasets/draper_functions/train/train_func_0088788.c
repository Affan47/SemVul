nfs3_fh_resolve_inode_hard (nfs3_call_state_t *cs)
{
        int             ret = -EFAULT;
        nfs_user_t      nfu = {0, };

        if (!cs)
                return ret;

        gf_log (GF_NFS3, GF_LOG_TRACE, "FH hard resolution for: gfid 0x%s",
                uuid_utoa (cs->resolvefh.gfid));
	cs->hardresolved = 1;
        nfs_loc_wipe (&cs->resolvedloc);
        ret = nfs_gfid_loc_fill (cs->vol->itable, cs->resolvefh.gfid,
                                 &cs->resolvedloc, NFS_RESOLVE_CREATE);
        if (ret < 0) {
                gf_log (GF_NFS3, GF_LOG_ERROR, "Failed to fill loc using gfid: "
                        "%s", strerror (-ret));
                goto out;
        }

        nfs_user_root_create (&nfu);
        ret = nfs_lookup (cs->nfsx, cs->vol, &nfu, &cs->resolvedloc,
                          nfs3_fh_resolve_inode_lookup_cbk, cs);

out:
        return ret;
}
