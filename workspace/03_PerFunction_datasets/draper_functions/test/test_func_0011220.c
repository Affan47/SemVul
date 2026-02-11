qif_get_accts_helper(gpointer obj, gpointer htp)
{
    QifTxn txn = obj;
    QifSplit split;
    GHashTable *ht = htp;
    GList *node;

    if (txn->from_acct)
        g_hash_table_insert(ht, txn->from_acct, txn->from_acct);


    for (node = txn->splits; node; node = node->next)
    {
        split = node->data;
        if (split->cat.obj && split->cat_is_acct)
            g_hash_table_insert(ht, split->cat.acct, split->cat.acct);
    }
}
