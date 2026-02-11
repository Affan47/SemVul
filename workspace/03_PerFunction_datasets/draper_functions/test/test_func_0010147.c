e2_window_update_status_bar (gpointer userdata)
{


#ifdef E2_STATUS_BLOCK
	if (app.status_working)
	{
		printd (DEBUG, "update status bar BLOCKED");
		return TRUE;
	}
#endif

#ifdef E2_STATUS_BLOCK
	app.status_working = TRUE;
#endif
	gint selected_rows, total_rows;
	GtkTreeModel *model = gtk_tree_view_get_model (GTK_TREE_VIEW (curr_view->treeview));
	GtkTreeSelection *sel = curr_view->selection;

	selected_rows = gtk_tree_selection_count_selected_rows (sel);
	total_rows = gtk_tree_model_iter_n_children (model, NULL);
	if ((selected_rows != last_selected_rows) || (total_rows != last_total_rows))
	{
		if (e2_option_bool_get ("show-updir-entry"))
		{


			GtkTreeIter iter;
			if (gtk_tree_model_get_iter_first (model, &iter))
			{
				total_rows--;
				if (gtk_tree_selection_iter_is_selected (sel, &iter))
					selected_rows--;
			}
		}
		last_selected_rows = selected_rows;
		last_total_rows = total_rows;
		gchar *status_text1 = (curr_view->total_items > total_rows) ?
			g_strdup_printf (_("displayed & %d concealed "), curr_view->total_items-total_rows) :
			"" ;
		gchar *status_text2 = g_strdup_printf (
			_("%s%d selected item(s) of %d %sin %s"), ":::  ",
#ifdef E2_VFSTMP

#else
			selected_rows, total_rows, status_text1, curr_view->dir);
#endif


#ifdef E2_VFSTMP

#else
		if (*(curr_view->dir + sizeof (gchar)) != '\0')
#endif
		{
			gint len = strlen (status_text2);
			*(status_text2 + len - sizeof (gchar)) = '\0';
		}
		gdk_threads_enter ();
		gtk_label_set_text (GTK_LABEL (app.status_bar_label2), status_text2);
		gdk_threads_leave ();
		if (*status_text1 != '\0')
			g_free (status_text1);
		g_free (status_text2);
	}
#ifdef E2_STATUS_BLOCK
	app.status_working = FALSE;
#endif

	return TRUE;
}
