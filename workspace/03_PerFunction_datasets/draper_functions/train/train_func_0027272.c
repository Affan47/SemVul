nfs3_fh_resolve_inode (nfs3_call_state_t *cs)
{
        inode_t         *inode = NULL;
        int             ret = -EFAULT;

        if (!cs)
                return ret;

        gf_log (GF_NFS3, GF_LOG_TRACE, "FH needs inode resolution");
        inode = inode_find (cs->vol->itable, cs->resolvefh.gfid);
        if (!inode)
                ret = nfs3_fh_resolve_inode_hard (cs);
        else
                ret = nfs3_fh_resolve_inode_done (cs, inode);

        if (inode)
                inode_unref (inode);

        return ret;
}
