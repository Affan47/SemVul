qif_txn_destroy(QifObject obj)
{
    QifTxn txn = (QifTxn) obj;
    GList *node;
    QifSplit split;

    g_free(txn->datestr);
    g_free(txn->payee);
    g_free(txn->address);
    g_free(txn->num);

    if (txn->invst_info)
        qif_txn_invst_destroy(txn->invst_info);

    for (node = txn->splits; node; node = node->next)
    {
        split = node->data;
        if (split == txn->default_split)
            txn->default_split = NULL;
        if (split == txn->current_split)
            txn->current_split = NULL;

        qif_split_destroy(split);
    }

    g_list_free(txn->splits);
    qif_split_destroy(txn->default_split);
    qif_split_destroy(txn->current_split);

    g_free(txn);
}
