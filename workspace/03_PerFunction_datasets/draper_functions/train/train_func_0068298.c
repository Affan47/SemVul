go_image_sel_new (GODoc *doc, GOCmdContext *cc, GOImage **image)
{
	GOImageSelState *state;
	GtkWidget *w;
	GHashTable *hash;

	g_return_val_if_fail (doc, NULL);

	if (image == NULL)
		return NULL;

	state = g_new0 (GOImageSelState, 1);
	state->doc = doc;
	state->cc = cc;
	state->result = image;
	state->gui = go_gtk_builder_load_internal ("res:go:gtk/go-image-sel.ui", GETTEXT_PACKAGE, state->cc);
        if (state->gui == NULL) {
		g_free (state);
                return NULL;
	}

	w = go_gtk_builder_get_widget (state->gui, "file-image-select");
	g_signal_connect (G_OBJECT (w),
		"clicked",
		G_CALLBACK (cb_file_image_select), state);

	state->icon_view = GTK_ICON_VIEW (gtk_builder_get_object (state->gui, "image-iconview"));
	state->model = gtk_list_store_new (2, GDK_TYPE_PIXBUF, G_TYPE_STRING);
	gtk_icon_view_set_model (state->icon_view , GTK_TREE_MODEL (state->model));
	gtk_icon_view_set_text_column (state->icon_view, 1);
	gtk_icon_view_set_pixbuf_column (state->icon_view, 0);
	g_object_unref (state->model);


	hash = go_doc_get_images (doc);
	if (hash)
		g_hash_table_foreach (hash, (GHFunc) add_image_cb, state);


	gtk_tree_sortable_set_default_sort_func (GTK_TREE_SORTABLE (state->model),
					       sort_func,
					       NULL, NULL);
	gtk_tree_sortable_set_sort_column_id (GTK_TREE_SORTABLE (state->model),
					    GTK_TREE_SORTABLE_DEFAULT_SORT_COLUMN_ID,
					    GTK_SORT_ASCENDING);
	g_signal_connect (state->icon_view, "selection-changed", G_CALLBACK (cb_selection_changed), state);


	state->ok_button = go_gtk_builder_get_widget (state->gui, "ok-button");
	g_signal_connect (state->ok_button, "clicked", G_CALLBACK (ok_button_clicked_cb), state);
	gtk_widget_set_sensitive (state->ok_button, FALSE);
	w = go_gtk_builder_get_widget (state->gui, "cancel-button");
	g_signal_connect (w, "clicked", G_CALLBACK (cancel_button_clicked_cb), state);

	state->dialog = go_gtk_builder_get_widget (state->gui, "go-image-sel");
	g_signal_connect (state->dialog, "delete-event", G_CALLBACK (delete_event_cb), state);
	return state->dialog;
}
