afr_compute_txn_changelog (afr_local_t *local, afr_private_t *priv)
{
        int             i = 0;
        int             index = 0;
        int32_t         postop = 0;
        int32_t         preop = 1;
        int32_t         **txn_changelog = NULL;

        txn_changelog = local->transaction.txn_changelog;
        index = afr_index_for_transaction_type (local->transaction.type);
        for (i = 0; i < priv->child_count; i++) {
                postop = ntoh32 (local->pending[i][index]);
                txn_changelog[i][index] = hton32 (postop + preop);
        }
}
