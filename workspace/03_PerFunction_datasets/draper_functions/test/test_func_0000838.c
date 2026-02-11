gm_world_properties_dialog_update_trigger(GmWorldPropertiesDialog *properties,
		GtkTreeIter *iter, GmTrigger *t) {
	GtkTreeView *tree_view = GTK_TREE_VIEW(properties->tree_view_triggers);
	GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(tree_view));
	gchar *text;

	text = g_strdup_printf(_("<b>%s</b>\nConditions: %d\nActions: %d"),
			t->name, g_list_length(t->conditions), g_list_length(t->actions));
	gtk_list_store_set(store, iter, 1, text, 2, t, -1);

	switch (t->event) {
		case TT_OUTPUT:
			gtk_list_store_set(store, iter, 0,
					gm_pixbuf_get_at_size("world.svg", 32, 32), -1);
		break;
		case TT_USERS:
			gtk_list_store_set(store, iter, 0,
					gm_pixbuf_get_at_size("ice-userlist/programmer.svg", 32,
					32), -1);
		break;
		default:
		break;
	}

	g_free(text);
}
