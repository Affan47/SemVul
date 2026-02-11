afr_build_sources (xlator_t *this, dict_t **xattr, struct iatt *bufs,
                   int32_t **pending_matrix, int32_t *sources,
                   int32_t *success_children, afr_transaction_type type)
{
        afr_private_t           *priv = NULL;
        afr_self_heal_type      sh_type    = AFR_SELF_HEAL_INVALID;
        int                     nsources   = -1;

        priv = this->private;

        if (afr_get_children_count (success_children, priv->child_count) == 0)
                goto out;

        afr_build_pending_matrix (priv->pending_key, pending_matrix,
                                  xattr, type, priv->child_count);

        sh_type = afr_self_heal_type_for_transaction (type);
        if (AFR_SELF_HEAL_INVALID == sh_type)
                goto out;

        afr_sh_print_pending_matrix (pending_matrix, this);

        nsources = afr_mark_sources (sources, pending_matrix, bufs,
                                     priv->child_count, sh_type,
                                     success_children, this->name);
out:
        return nsources;
}
