gnc_entry_ledger_move_cursor (VirtualLocation *p_new_virt_loc,
        gpointer user_data)
{
    GncEntryLedger *ledger = user_data;
    VirtualLocation new_virt_loc = *p_new_virt_loc;
    GncEntry *new_entry;
    GncEntry *old_entry;
    gboolean saved;

    if (!ledger) return;

    old_entry = gnc_entry_ledger_get_current_entry (ledger);
    new_entry = gnc_entry_ledger_get_entry (ledger, new_virt_loc.vcell_loc);

    gnc_suspend_gui_refresh ();
    saved = gnc_entry_ledger_save (ledger, old_entry != new_entry);
    gnc_resume_gui_refresh ();


    if (saved)
    {
        VirtualCellLocation vcell_loc;


        gnc_entry_ledger_display_refresh (ledger);

        if (ledger->traverse_to_new)
            new_entry = gnc_entry_ledger_get_blank_entry (ledger);


        if (gnc_entry_ledger_find_entry (ledger, new_entry, &vcell_loc))
        {
            gnc_table_get_virtual_cell (ledger->table, vcell_loc);
            new_virt_loc.vcell_loc = vcell_loc;
        }
        else
            new_virt_loc.vcell_loc = ledger->table->current_cursor_loc.vcell_loc;
    }

    gnc_table_find_close_valid_cell (ledger->table, &new_virt_loc, FALSE);

    *p_new_virt_loc = new_virt_loc;
}
