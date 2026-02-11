xaccSplitGetOtherSplit (const Split *split)
{
    int i;
    Transaction *trans;
    int count, num_splits;
    Split *other = NULL;
    KvpValue *sva;
    gboolean trading_accts;

    if (!split) return NULL;
    trans = split->parent;
    if (!trans) return NULL;

#ifdef OLD_ALGO_HAS_ONLY_TWO_SPLITS
    Split *s1, *s2;
    if (g_list_length (trans->splits) != 2) return NULL;

    s1 = g_list_nth_data (trans->splits, 0);
    s2 = g_list_nth_data (trans->splits, 1);

    if (s1 == split) return s2;
    return s1;
#endif

    trading_accts = xaccTransUseTradingAccounts (trans);
    num_splits = xaccTransCountSplits(trans);
    count = num_splits;
    sva = kvp_frame_get_slot (split->inst.kvp_data, "lot-split");
    if (!sva && !trading_accts && (2 != count)) return NULL;

    for (i = 0; i < num_splits; i++)
    {
        Split *s = xaccTransGetSplit(trans, i);
        if (s == split)
        {
            --count;
            continue;
        }
        if (kvp_frame_get_slot (s->inst.kvp_data, "lot-split"))
        {
            --count;
            continue;
        }
        if (trading_accts &&
                xaccAccountGetType(xaccSplitGetAccount(s)) == ACCT_TYPE_TRADING)
        {
            --count;
            continue;
        }
        other = s;
    }
    return (1 == count) ? other : NULL;
}
