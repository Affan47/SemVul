add_button_clicked_callback (GtkWidget            *button,
			     GeditEncodingsDialog *dialog)
{
	GtkTreeSelection *selection;
	GSList *encodings;
	GSList *tmp;

	selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (dialog->priv->available_treeview));

	encodings = NULL;
	gtk_tree_selection_selected_foreach (selection,
					     get_selected_encodings_func,
					     &encodings);

	tmp = encodings;
	while (tmp != NULL)
	{
		if (g_slist_find (dialog->priv->show_in_menu_list, tmp->data) == NULL)
		{
			dialog->priv->show_in_menu_list = g_slist_prepend (dialog->priv->show_in_menu_list,
									   tmp->data);
		}

		tmp = g_slist_next (tmp);
	}

	g_slist_free (encodings);

	update_shown_in_menu_tree_model (GTK_LIST_STORE (dialog->priv->displayed_liststore),
					 dialog->priv->show_in_menu_list);
}
