gm_world_properties_dialog_remove_trigger(GmWorldPropertiesDialog *properties,
		GtkTreeIter *iter) {
	GtkTreeView *tree_view = GTK_TREE_VIEW(properties->tree_view_triggers);
	GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(tree_view));

	gtk_list_store_remove(store, iter);

	if (gtk_tree_model_iter_n_children(GTK_TREE_MODEL(store), NULL) == 0) {
		gtk_widget_set_sensitive(gm_world_properties_dialog_widget(properties,
				"button_edit_trigger"), FALSE);
		gtk_widget_set_sensitive(gm_world_properties_dialog_widget(properties,
				"button_delete_trigger"), FALSE);
	}
}
