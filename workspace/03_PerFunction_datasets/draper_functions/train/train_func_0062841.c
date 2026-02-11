on_row_changed(GtkTreePath* path,
                                                   GtkTreeIter* iter)
{


	GtkTreeIter sel_iter;

	if(inf_gtk_browser_view_get_selected(m_view, &sel_iter))
	{


		GtkTreePath* sel_path = gtk_tree_model_get_path(
			GTK_TREE_MODEL(m_filter_model), &sel_iter);
		if(gtk_tree_path_compare(path, sel_path) == 0)
		{
			GtkTreeIter dummy_iter;
			if(!gtk_tree_model_iter_parent(
				GTK_TREE_MODEL(m_filter_model), &dummy_iter,
				iter))
			{
				InfGtkBrowserModelStatus s;
				gtk_tree_model_get(
					GTK_TREE_MODEL(m_filter_model), iter,
					INF_GTK_BROWSER_MODEL_COL_STATUS, &s,
					-1);

				set_response_sensitive(
					Gtk::RESPONSE_ACCEPT,
					s == INF_GTK_BROWSER_MODEL_CONNECTED
				);
			}
		}

		gtk_tree_path_free(sel_path);
	}
}
