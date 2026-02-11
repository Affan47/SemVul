nfs_inode_loc_fill (inode_t *inode, loc_t *loc)
{
        char            *resolvedpath = NULL;
        inode_t         *parent = NULL;
        int             ret = -EFAULT;

        if ((!inode) || (!loc))
                return ret;

        if ((inode) && __is_root_gfid (inode->gfid))
                goto ignore_parent;

        parent = inode_parent (inode, 0, NULL);
        if (!parent)
                goto err;

ignore_parent:
        ret = inode_path (inode, NULL, &resolvedpath);
        if (ret < 0) {
                gf_log (GF_NFS, GF_LOG_ERROR, "path resolution failed %s",
                                resolvedpath);
                goto err;
        }

        ret = nfs_loc_fill (loc, inode, parent, resolvedpath);
        if (ret < 0) {
                gf_log (GF_NFS, GF_LOG_ERROR, "loc fill resolution failed %s",
                                resolvedpath);
                goto err;
        }

err:
        if (parent)
                inode_unref (parent);

        if (resolvedpath)
                GF_FREE (resolvedpath);

        return ret;
}
