gnc_entry_ledger_refresh_internal (GncEntryLedger *ledger, GList *entries)
{
    if (!ledger || ledger->loading)
        return;


    if (!ledger->full_refresh)
    {
        gnc_entry_ledger_load_xfer_cells (ledger);
        return;
    }


    if ((ledger->type == GNCENTRY_ORDER_VIEWER ||
            ledger->type == GNCENTRY_INVOICE_VIEWER ||
            ledger->type == GNCENTRY_BILL_VIEWER ||
            ledger->type == GNCENTRY_EXPVOUCHER_VIEWER) && !entries)
        return;

    ledger->loading = TRUE;
    gnc_entry_ledger_load (ledger, entries);
    ledger->loading = FALSE;
}
