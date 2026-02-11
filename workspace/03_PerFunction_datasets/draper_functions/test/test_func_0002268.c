xaccAccountAssignLots (Account *acc)
{
    SplitList *splits, *node;

    if (!acc) return;

    ENTER ("acc=%s", xaccAccountGetName(acc));
    xaccAccountBeginEdit (acc);

restart_loop:
    splits = xaccAccountGetSplitList(acc);
    for (node = splits; node; node = node->next)
    {
        Split * split = node->data;


        if (split->lot) continue;


        if (gnc_numeric_zero_p (split->amount) &&
                xaccTransGetVoidStatus(split->parent)) continue;

        if (xaccSplitAssign (split)) goto restart_loop;
    }
    xaccAccountCommitEdit (acc);
    LEAVE ("acc=%s", xaccAccountGetName(acc));
}
