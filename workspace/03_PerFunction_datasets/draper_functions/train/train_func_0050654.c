icon_chooser_ok_clicked(GtkButton *button,
					ToolbarPage *prefs_toolbar)
{
	GtkTreeModel *model;
	GtkTreeIter iter;
	GList *list;
	GdkPixbuf *pix;
	gchar *icon_file;

	cm_return_if_fail(prefs_toolbar != NULL);

	model = gtk_icon_view_get_model(GTK_ICON_VIEW(prefs_toolbar->icon_chooser_view));
	list = gtk_icon_view_get_selected_items(GTK_ICON_VIEW(prefs_toolbar->icon_chooser_view));
	if(list == NULL)
		return;

	if(!gtk_tree_model_get_iter(model, &iter, (GtkTreePath *)list->data)) {
		gtk_tree_path_free(list->data);
		g_list_free(list);
		return;
	}

	gtk_tree_model_get(model, &iter,
			   SET_ICON, &pix,
			   SET_FILENAME, &icon_file,
			   -1);

	g_free(prefs_toolbar->item_icon_file);
	prefs_toolbar->item_icon_file = icon_file;
	gtk_button_set_image(GTK_BUTTON(prefs_toolbar->icon_button),
			     gtk_image_new_from_pixbuf(pix));

	gtk_widget_destroy(prefs_toolbar->icon_chooser_win);
	prefs_toolbar->icon_chooser_win = NULL;
	prefs_toolbar->icon_chooser_view = NULL;

	gtk_tree_path_free(list->data);
	g_list_free(list);
}
