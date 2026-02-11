afr_sh_inode_set_read_ctx (afr_self_heal_t *sh, xlator_t *this)
{
        afr_private_t   *priv = NULL;
        int             ret = 0;
        int             i = 0;

        priv = this->private;
        sh->source = afr_sh_select_source (sh->sources, priv->child_count);
        if (sh->source < 0) {
                ret = -1;
                goto out;
        }


        for (i = 0; i < priv->child_count; i++) {
                if (i == sh->source || sh->child_errno[i])
                        continue;

                if (SIZE_DIFFERS (&sh->buf[i], &sh->buf[sh->source]))
                        sh->sources[i] = 0;
        }

        afr_reset_children (sh->fresh_children, priv->child_count);
        afr_get_fresh_children (sh->success_children, sh->sources,
                                sh->fresh_children, priv->child_count);
        afr_inode_set_read_ctx (this, sh->inode, sh->source,
                                sh->fresh_children);
out:
        return ret;
}
