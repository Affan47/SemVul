gnc_combo_cell_add_menu_item (ComboCell *cell, const char * menustr)
{
    PopBox *box;

    if (cell == NULL)
        return;
    if (menustr == NULL)
        return;

    box = cell->cell.gui_private;

    if (box->item_list != NULL)
    {
        block_list_signals (cell);

        gnc_item_list_append (box->item_list, menustr);
        if (cell->cell.value &&
                (strcmp (menustr, cell->cell.value) == 0))
            gnc_item_list_select (box->item_list, menustr);

        unblock_list_signals (cell);
    }
    else
    {
        GtkTreeIter iter;

        gtk_list_store_append(box->tmp_store, &iter);
        gtk_list_store_set(box->tmp_store, &iter, 0, menustr, -1);
    }


    if (FALSE == box->use_quickfill_cache)
    {
        gnc_quickfill_insert (box->qf, menustr, QUICKFILL_ALPHA);
    }
}
