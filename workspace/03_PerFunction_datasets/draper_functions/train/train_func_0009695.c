get_taxval_entry (VirtualLocation virt_loc,
                                      gboolean translate,
                                      gboolean *conditionally_changed,
                                      gpointer user_data)
{
    GncEntryLedger *ledger = user_data;
    gnc_numeric value;


    if (virt_cell_loc_equal (ledger->table->current_cursor_loc.vcell_loc,
                             virt_loc.vcell_loc))
    {


        gnc_entry_ledger_compute_value (ledger, NULL, &value);
    }
    else
    {
        GncEntry *entry = gnc_entry_ledger_get_entry (ledger, virt_loc.vcell_loc);

        if (entry == gnc_entry_ledger_get_blank_entry (ledger))
            return NULL;


        value = gncEntryGetDocTaxValue (entry, TRUE, ledger->is_cust_doc, ledger->is_credit_note);
    }

    return xaccPrintAmount (value, gnc_default_print_info (FALSE));
}
