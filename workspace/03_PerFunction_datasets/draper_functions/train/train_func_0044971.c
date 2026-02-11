afr_set_postop_dict (afr_local_t *local, xlator_t *this, dict_t *xattr,
                     int optimized, int child)
{
        int32_t                 **txn_changelog = NULL;
        int32_t                 **changelog = NULL;
        afr_private_t           *priv = NULL;
        int                     ret = 0;
        afr_xattrop_type_t      op = LOCAL_LAST;

        priv = this->private;
        txn_changelog = local->transaction.txn_changelog;
        op = afr_get_postop_xattrop_type (local->pending, optimized, child,
                                          local->transaction.type);
        if (optimized)
                changelog = txn_changelog;
        else
                changelog = local->pending;
        ret = afr_set_pending_dict (priv, xattr, changelog, child, op);
        if (ret < 0)
                gf_log (this->name, GF_LOG_INFO,
                        "failed to set pending entry");
}
