nfs_fop_local_wipe (xlator_t *nfsx, struct nfs_fop_local *l)
{
        if ((!nfsx) || (!l))
                return;

        if (l->iobref)
                iobref_unref (l->iobref);

        if (l->parent)
                inode_unref (l->parent);

        if (l->inode)
                inode_unref (l->inode);

        if (l->newparent)
                inode_unref (l->newparent);

        if (l->dictgfid)
                dict_unref (l->dictgfid);

        mem_put (l);

        return;
}
