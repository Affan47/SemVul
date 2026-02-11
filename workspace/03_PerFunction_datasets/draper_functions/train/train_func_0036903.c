get_qty_io_flags (VirtualLocation virt_loc, gpointer user_data)
{
    GncEntryLedger *ledger = user_data;
    GncEntry *entry;
    CellIOFlags flags = get_standard_io_flags (virt_loc, user_data);


    if (!ledger->is_cust_doc || flags == XACC_CELL_ALLOW_SHADOW)
        return flags;


    entry = gnc_entry_ledger_get_entry (ledger, virt_loc.vcell_loc);
    if (gncEntryGetBillable (entry))
        return XACC_CELL_ALLOW_SHADOW;

    return flags;
}
