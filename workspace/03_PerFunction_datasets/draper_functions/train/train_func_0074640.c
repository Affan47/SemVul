xaccAccountScrubLots (Account *acc)
{
    LotList *lots, *node;
    if (!acc) return;
    if (FALSE == xaccAccountHasTrades (acc)) return;

    ENTER ("(acc=%s)", xaccAccountGetName(acc));
    xaccAccountBeginEdit(acc);
    xaccAccountAssignLots (acc);

    lots = xaccAccountGetLotList(acc);
    for (node = lots; node; node = node->next)
    {
        GNCLot *lot = node->data;
        xaccScrubLot (lot);
    }
    g_list_free(lots);
    xaccAccountCommitEdit(acc);
    LEAVE ("(acc=%s)", xaccAccountGetName(acc));
}
