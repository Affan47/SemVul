gnc_ledger_display2_set_query (GNCLedgerDisplay2 *ledger_display, Query *q)
{
    if (!ledger_display || !q)
        return;

    g_return_if_fail (ledger_display->ld_type == LD2_GL);

    qof_query_destroy (ledger_display->query);
    ledger_display->query = qof_query_copy (q);
}
