insert_split (Account *parent, Transaction *txn, SplitParms *p)
{
    QofBook *book = gnc_account_get_book (parent);
    Split *split = xaccMallocSplit (book);
    Account *acct = gnc_account_lookup_by_name (parent, p->account);
    LotList* lotlist = xaccAccountGetLotList (acct);
    GNCLot* lot = NULL;
    g_assert (acct != NULL);
    xaccSplitSetParent (split, txn);
    xaccSplitSetMemo (split, p->memo);
    xaccSplitSetReconcile (split, (p->reconciled ? p->reconciled : NREC));
    g_object_set (split,
                  "account", acct,
                  "memo", p->memo,
                  "amount", &(p->amount),
                  "value", &(p->value),
                  NULL);

    gnc_account_insert_split (acct, split);
    if (p->lotnum == 0)
        return split;

    if (p->lotnum > g_list_length (lotlist))
        lot = gnc_lot_new (book);
    else
        lot = GNC_LOT (g_list_nth_data (lotlist, p->lotnum - 1));

    gnc_lot_add_split (lot, split);
    return split;
}
