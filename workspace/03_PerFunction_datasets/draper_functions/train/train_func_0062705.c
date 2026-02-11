gtk_column_chooser_get_column(GtkColumnChooser *cc, GtkWidget *widget)
{
    g_return_val_if_fail(widget != NULL, NULL);
	g_return_val_if_fail(cc != NULL, NULL);

    return htable_lookup(cc->col_map, widget);
}
