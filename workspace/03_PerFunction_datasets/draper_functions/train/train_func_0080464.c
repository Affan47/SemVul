get_history_store (GsearchHistoryEntry *entry)
{
	GtkTreeModel *store;

	store = gtk_combo_box_get_model (GTK_COMBO_BOX (entry));
	g_return_val_if_fail (GTK_IS_LIST_STORE (store), NULL);

	return (GtkListStore *) store;
}
