mnt3svc_volume_mount (rpcsvc_request_t *req, struct mount3_state *ms,
                      struct mnt3_export *exp)
{
        inode_t         *exportinode = NULL;
        int             ret = -EFAULT;
        uuid_t          rootgfid = {0, };

        if ((!req) || (!exp) || (!ms))
                return ret;

        rootgfid[15] = 1;
        exportinode = inode_find (exp->vol->itable, rootgfid);
        if (!exportinode) {
                gf_log (GF_MNT, GF_LOG_ERROR, "Failed to get root inode");
                ret = -ENOENT;
                goto err;
        }

        ret = mnt3svc_mount_inode (req, ms, exp->vol, exportinode);
        inode_unref (exportinode);

err:
        return ret;
}
