afr_transaction_rm_stale_children (call_frame_t *frame, xlator_t *this,
                                   inode_t *inode, afr_transaction_type type)
{
        int             i = -1;
        int             count = 0;
        int             read_child = -1;
        afr_private_t   *priv = NULL;
        afr_local_t     *local = NULL;
        int             **pending = NULL;
        int             idx = 0;
        int32_t         *stale_children = NULL;
        int32_t         *fresh_children = NULL;
        gf_boolean_t    rm_stale_children = _gf_false;

        idx = afr_index_for_transaction_type (type);

        priv = this->private;
        local = frame->local;
        pending = local->pending;

        if (local->op_ret < 0)
                goto out;
        fresh_children = local->fresh_children;
        read_child = afr_inode_get_read_ctx (this, inode, fresh_children);
        if (read_child < 0) {
                gf_log (this->name, GF_LOG_DEBUG, "Possible split-brain "
                        "for %s", uuid_utoa (inode->gfid));
                goto out;
        }

        for (i = 0; i < priv->child_count; i++) {
                if (!afr_is_child_present (fresh_children,
                                           priv->child_count, i))
                        continue;
                if (pending[i][idx])
                        continue;

                if (!stale_children)
                        stale_children = afr_children_create (priv->child_count);
                if (!stale_children)
                        goto out;

                rm_stale_children = _gf_true;
                stale_children[count++] = i;
                gf_log (this->name, GF_LOG_DEBUG, "Removing stale child "
                        "%d for %s", i, uuid_utoa (inode->gfid));
        }

        if (!rm_stale_children)
                goto out;

        afr_inode_rm_stale_children (this, inode, stale_children);
out:
        GF_FREE (stale_children);
        return;
}
