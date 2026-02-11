clipboard_contents_received_callback (GtkClipboard     *clipboard,
				      GtkSelectionData *selection_data,
				      gpointer          data)
{
	FMTreeView *view;

	view = FM_TREE_VIEW (data);

	if (gtk_selection_data_get_data_type (selection_data) == copied_files_atom
	    && gtk_selection_data_get_length (selection_data) > 0 &&
	    view->details->popup != NULL) {
		gtk_widget_set_sensitive (view->details->popup_paste, TRUE);
	}

	g_object_unref (view);
}
