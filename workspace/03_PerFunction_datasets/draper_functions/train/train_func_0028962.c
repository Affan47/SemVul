dcc_fill_window (int flags)
{
	struct DCC *dcc;
	GSList *list;
	GtkTreeIter iter;
	int i = 0;

	gtk_list_store_clear (GTK_LIST_STORE (dccfwin.store));

	if (flags & VIEW_UPLOAD)
	{
		list = dcc_list;
		while (list)
		{
			dcc = list->data;
			if (dcc->type == TYPE_SEND)
			{
				dcc_append (dcc, dccfwin.store, FALSE);
				i++;
			}
			list = list->next;
		}
	}

	if (flags & VIEW_DOWNLOAD)
	{
		list = dcc_list;
		while (list)
		{
			dcc = list->data;
			if (dcc->type == TYPE_RECV)
			{
				dcc_append (dcc, dccfwin.store, FALSE);
				i++;
			}
			list = list->next;
		}
	}


	if (i == 1)
	{
		gtk_tree_model_get_iter_first (GTK_TREE_MODEL (dccfwin.store), &iter);
		gtk_tree_selection_select_iter (dccfwin.sel, &iter);
	}

	update_clear_button_sensitivity ();
}
