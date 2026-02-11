mimeview_selected(GtkTreeSelection *selection, MimeView *mimeview)
{
	GtkTreeView *ctree = GTK_TREE_VIEW(mimeview->ctree);
	GtkTreeModel *model;
	GtkTreeIter iter;
	GtkTreePath *path;
	MimeInfo *partinfo;

	selection = gtk_tree_view_get_selection(ctree);
	if (!gtk_tree_selection_get_selected(selection, &model, &iter))
		return;

	path = gtk_tree_model_get_path(model, &iter);

	if (mimeview->opened && !gtk_tree_path_compare(mimeview->opened, path)) {
		gtk_tree_path_free(path);
		return;
	}

	gtk_tree_path_free(mimeview->opened);
	mimeview->opened = path;
	mimeview->spec_part = NULL;
	gtk_tree_view_scroll_to_cell(ctree, path, NULL, TRUE, 0.5, 0);

	partinfo = mimeview_get_node_part(mimeview, path);
	if (!partinfo) return;


	if (gtk_widget_has_grab(GTK_WIDGET(ctree))) {
		gtk_grab_remove(GTK_WIDGET(ctree));
		if (gdk_pointer_is_grabbed())
			gdk_pointer_ungrab(GDK_CURRENT_TIME);
	}

	mimeview->textview->default_text = FALSE;

	update_signature_info(mimeview, partinfo);

	if (!mimeview_show_part(mimeview, partinfo)) {
		switch (partinfo->type) {
		case MIMETYPE_TEXT:
		case MIMETYPE_MESSAGE:
		case MIMETYPE_MULTIPART:
			mimeview_show_message_part(mimeview, partinfo);

			break;
		default:
			mimeview->textview->default_text = TRUE;
			mimeview_change_view_type(mimeview, MIMEVIEW_TEXT);
			textview_clear(mimeview->textview);
			textview_show_mime_part(mimeview->textview, partinfo);
			break;
		}
	}

	if (mimeview->siginfo && privacy_auto_check_signatures(mimeview->siginfo)) {
		mimeview_check_signature(mimeview);
	}
}
