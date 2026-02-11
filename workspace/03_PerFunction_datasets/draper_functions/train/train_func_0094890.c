nfs_inode_unlink (xlator_t *nfsx, xlator_t *xl, nfs_user_t *nfu, loc_t *pathloc,
                  fop_unlink_cbk_t cbk, void *local)
{
        struct nfs_fop_local            *nfl = NULL;
        int                             ret = -EFAULT;

        if ((!nfsx) || (!xl) || (!pathloc) || (!nfu))
                return -EFAULT;

        nfs_fop_handle_local_init (NULL, nfsx, nfl, cbk, local, ret, err);
        nfl_inodes_init (nfl, pathloc->inode, pathloc->parent, NULL,
                         pathloc->name, NULL);
        ret = nfs_fop_unlink (nfsx, xl, nfu, pathloc, nfs_inode_unlink_cbk,nfl);

err:
        if (ret < 0)
                nfs_fop_local_wipe (xl, nfl);

        return ret;
}
