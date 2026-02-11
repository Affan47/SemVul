dupe_menu_add_item(GtkListStore *store, const gchar *text, DupeMatchType type, DupeWindow *dw)
{
	GtkTreeIter iter;

	gtk_list_store_append(store, &iter);
	gtk_list_store_set(store, &iter, DUPE_MENU_COLUMN_NAME, text,
					 DUPE_MENU_COLUMN_MASK, type, -1);

	if (dw->match_mask == type) gtk_combo_box_set_active_iter(GTK_COMBO_BOX(dw->combo), &iter);
}
