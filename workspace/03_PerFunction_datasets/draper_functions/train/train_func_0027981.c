xaccSplitRetDateReconciledTS (const Split * split)
{
    Timespec ts = {0, 0};
    return split ? split->date_reconciled : ts;
}
