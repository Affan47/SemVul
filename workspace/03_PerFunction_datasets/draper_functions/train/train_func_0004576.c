gnc_combo_cell_set_sort_enabled (ComboCell *cell, gboolean enabled)
{
    PopBox *box;

    if (cell == NULL)
        return;

    box = cell->cell.gui_private;
    if (box->item_list == NULL)
        return;

    block_list_signals (cell);
    gnc_item_list_set_sort_enabled(box->item_list, enabled);
    unblock_list_signals (cell);
}
