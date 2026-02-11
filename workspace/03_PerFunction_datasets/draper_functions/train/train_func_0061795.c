gnucash_sheet_create (Table *table)
{
    GnucashSheet *sheet;
    GnomeCanvas  *canvas;

    ENTER("table=%p", table);

    sheet = g_object_new (GNUCASH_TYPE_SHEET, NULL);
    canvas = GNOME_CANVAS (sheet);

    sheet->table = table;
    sheet->entry = NULL;

    sheet->vadj = gtk_layout_get_vadjustment (GTK_LAYOUT(canvas));
    sheet->hadj = gtk_layout_get_hadjustment (GTK_LAYOUT(canvas));

    g_signal_connect (G_OBJECT (sheet->vadj), "value_changed",
                      G_CALLBACK (gnucash_sheet_vadjustment_value_changed), sheet);
    g_signal_connect (G_OBJECT (sheet->hadj), "changed",
                      G_CALLBACK (gnucash_sheet_hadjustment_changed), sheet);

    LEAVE("%p", sheet);
    return sheet;
}
