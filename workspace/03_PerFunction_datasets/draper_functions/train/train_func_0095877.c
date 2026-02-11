select_data_cb(GtkTreeSelection *selection, gpointer user_data)
{
	GtkTreeIter iter;
	data *my_data;
	char *s_title;
	char *message;
	GtkTextIter start, end;

	if (!gtk_tree_selection_get_selected(selection, NULL, &iter)) {
		gtk_editable_delete_text(GTK_EDITABLE(title), 0, -1);
		gtk_text_buffer_get_bounds(buffer, &start, &end);
		gtk_text_buffer_delete(buffer, &start, &end);

		return;
	}

	gtk_tree_model_get(GTK_TREE_MODEL(data_clist_model), &iter,
		CLIST_DATA, &my_data, -1);

	s_title = my_data->title;
	message = my_data->message->str;

	gtk_entry_set_text(GTK_ENTRY(title), s_title);
	gtk_text_buffer_get_bounds(buffer, &start, &end);

	gtk_text_buffer_delete(buffer, &start, &end);
	gtk_text_buffer_insert_at_cursor(buffer, message, strlen(message));
}
