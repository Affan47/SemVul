gnc_table_verify_cursor_position (Table *table, VirtualLocation virt_loc)
{
    gboolean do_move = FALSE;
    gboolean moved_cursor = FALSE;

    if (!table) return FALSE;


    if (gnc_table_virtual_cell_out_of_bounds (table, virt_loc.vcell_loc))
        do_move = TRUE;

    if (!virt_cell_loc_equal (virt_loc.vcell_loc,
                              table->current_cursor_loc.vcell_loc))
        do_move = TRUE;

    if (do_move)
    {
        gnc_table_move_cursor_gui (table, virt_loc);
        moved_cursor = TRUE;
    }
    else if (!virt_loc_equal (virt_loc, table->current_cursor_loc))
    {
        table->current_cursor_loc = virt_loc;
        moved_cursor = TRUE;
    }

    return moved_cursor;
}
