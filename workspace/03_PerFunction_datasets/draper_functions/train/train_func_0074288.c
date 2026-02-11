gnc_ledger_display_refresh (GNCLedgerDisplay *ld)
{
    ENTER("ld=%p", ld);

    if (!ld)
    {
        LEAVE("no display");
        return;
    }

    if (ld->loading)
    {
        LEAVE("already loading");
        return;
    }

    gnc_ledger_display_refresh_internal (ld, qof_query_run (ld->query));
    LEAVE(" ");
}
