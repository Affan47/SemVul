msgwin_goto_messages_file_line(gboolean focus_editor)
{
	GtkTreeIter iter;
	GtkTreeModel *model;
	GtkTreeSelection *selection;
	gboolean ret = FALSE;

	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(msgwindow.tree_msg));
	if (gtk_tree_selection_get_selected(selection, &model, &iter))
	{
		gint line;
		gchar *string;
		GeanyDocument *doc;
		GeanyDocument *old_doc = document_get_current();

		gtk_tree_model_get(model, &iter, 0, &line, 1, &doc, 3, &string, -1);

		if (line >= 0 && DOC_VALID(doc))
		{
			ret = navqueue_goto_line(old_doc, doc, line);
			if (ret && focus_editor)
				gtk_widget_grab_focus(GTK_WIDGET(doc->editor->sci));
		}
		else if (line < 0 && string != NULL)
		{
			gchar *filename;


			msgwin_parse_generic_line(string, &filename, &line);
			if (filename != NULL)
			{

				doc = document_open_file(filename, FALSE, NULL, NULL);
				if (doc != NULL)
				{
					ret = (line < 0) ? TRUE : navqueue_goto_line(old_doc, doc, line);
					if (ret && focus_editor)
						gtk_widget_grab_focus(GTK_WIDGET(doc->editor->sci));
				}
			}
			g_free(filename);
		}
		g_free(string);
	}
	return ret;
}
