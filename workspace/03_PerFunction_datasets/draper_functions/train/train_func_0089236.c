nfs3_fh_resolve_inode_done (nfs3_call_state_t *cs, inode_t *inode)
{
        int             ret = -EFAULT;

        if ((!cs) || (!inode))
                return ret;

        gf_log (GF_NFS3, GF_LOG_TRACE, "FH inode resolved");
        ret = nfs_inode_loc_fill (inode, &cs->resolvedloc, NFS_RESOLVE_EXIST);
        if (ret < 0) {
                gf_log (GF_NFS3, GF_LOG_ERROR, "inode loc fill failed");
                goto err;
        }

        nfs3_call_resume (cs);

err:
        return ret;
}
