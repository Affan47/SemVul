afr_stale_child_up (afr_local_t *local, xlator_t *this)
{
        int             i = 0;
        afr_private_t   *priv = NULL;
        int             up = -1;

        priv = this->private;

        if (!local->fresh_children)
                local->fresh_children = afr_children_create (priv->child_count);
        if (!local->fresh_children)
                goto out;

        afr_inode_get_read_ctx (this, local->fd->inode, local->fresh_children);
        if (priv->child_count == afr_get_children_count (local->fresh_children,
                                                         priv->child_count))
                goto out;

        for (i = 0; i < priv->child_count; i++) {
                if (!local->child_up[i])
                        continue;
                if (afr_is_child_present (local->fresh_children,
                                          priv->child_count, i))
                        continue;
                up = i;
                break;
        }
out:
        return up;
}
