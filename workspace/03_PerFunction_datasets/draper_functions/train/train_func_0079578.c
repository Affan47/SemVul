qif_txn_fix_amounts(QifTxn txn, gnc_numeric amount)
{
    gnc_numeric sum = amount;
    QifSplit split;
    GList *node;

    g_return_if_fail(txn);


    if (!txn->current_split) return;


    for (node = txn->splits; node; node = node->next)
    {
        split = node->data;
        sum = gnc_numeric_add(sum, split->amount, GNC_DENOM_AUTO, GNC_HOW_DENOM_LCD);
    }


    if (!gnc_numeric_zero_p(sum))
        for (node = txn->splits; node; node = node->next)
        {
            split = node->data;
            split->amount = gnc_numeric_neg(split->amount);
        }
}
