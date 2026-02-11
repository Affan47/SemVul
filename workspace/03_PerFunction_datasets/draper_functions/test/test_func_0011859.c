gnucash_sheet_new (Table *table)
{
    GnucashSheet *sheet;
    GnomeCanvasItem *item;
    GnomeCanvasGroup *sheet_group;

    g_return_val_if_fail (table != NULL, NULL);

    sheet = gnucash_sheet_create (table);


    sheet_group = gnome_canvas_root (GNOME_CANVAS(sheet));


    item = gnome_canvas_item_new (sheet_group,
                                  gnucash_grid_get_type (),
                                  "sheet", sheet,
                                  NULL);
    sheet->grid = item;


    sheet->dimensions_hash_table = g_hash_table_new_full (g_int_hash,
                                   g_int_equal,
                                   g_free, NULL);


    sheet->cursor = gnucash_cursor_new (sheet_group);
    gnome_canvas_item_set (sheet->cursor,
                           "sheet", sheet,
                           "grid", sheet->grid,
                           NULL);


    sheet->entry = gtk_entry_new ();
    g_object_ref_sink(sheet->entry);


    sheet->item_editor = gnc_item_edit_new(sheet_group, sheet, sheet->entry);

    gnome_canvas_item_hide (GNOME_CANVAS_ITEM(sheet->item_editor));


    g_signal_connect_after(sheet, "realize",
                           G_CALLBACK(gnucash_sheet_realize_entry),
                           sheet->entry);

    gnucash_sheet_refresh_from_prefs(sheet);
    gnucash_sheet_create_color_hack(sheet);

    return GTK_WIDGET(sheet);
}
