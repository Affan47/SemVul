dht_local_wipe (xlator_t *this, dht_local_t *local)
{
        if (!local)
                return;

        loc_wipe (&local->loc);
        loc_wipe (&local->loc2);

        if (local->xattr)
                dict_unref (local->xattr);

        if (local->inode)
                inode_unref (local->inode);

        if (local->layout) {
                dht_layout_unref (this, local->layout);
                local->layout = NULL;
        }

        loc_wipe (&local->linkfile.loc);

        if (local->linkfile.xattr)
                dict_unref (local->linkfile.xattr);

        if (local->linkfile.inode)
                inode_unref (local->linkfile.inode);

        if (local->fd) {
                fd_unref (local->fd);
                local->fd = NULL;
        }

        if (local->params) {
                dict_unref (local->params);
                local->params = NULL;
        }

        if (local->xattr_req)
                dict_unref (local->xattr_req);

        if (local->selfheal.layout) {
                dht_layout_unref (this, local->selfheal.layout);
                local->selfheal.layout = NULL;
        }

        GF_FREE (local->newpath);

        GF_FREE (local->key);

        GF_FREE (local->rebalance.vector);

        if (local->rebalance.iobref)
                iobref_unref (local->rebalance.iobref);

        mem_put (local);
}
