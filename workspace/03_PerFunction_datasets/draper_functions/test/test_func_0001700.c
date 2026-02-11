dpaned_set_tabbed(gboolean tabbed)
{
	DISCONNECT_PAGE_SIGNALS();

	if (!tabbed)
	{
		gsize length;
		int *tab_ids;
		int i;

		g_object_ref(debug_notebook_right);
		gtk_container_remove(GTK_CONTAINER(hpaned), debug_notebook_right);

		tab_ids = config_get_tabs(&length);
		for (i = 0; i < length; i++)
		{
			GtkWidget *tab = tabs_get_tab((tab_id)tab_ids[i]);
			if (-1 == gtk_notebook_page_num(GTK_NOTEBOOK(debug_notebook_left), tab))
			{
				g_object_ref(tab);
				gtk_container_remove(GTK_CONTAINER(debug_notebook_right), tab);
				gtk_notebook_insert_page(GTK_NOTEBOOK(debug_notebook_left), tab, gtk_label_new(tabs_get_label(tab_ids[i])), i);
				g_object_unref(tab);
				gtk_notebook_set_tab_detachable(GTK_NOTEBOOK(debug_notebook_left), tab, TRUE);
				gtk_notebook_set_tab_reorderable(GTK_NOTEBOOK(debug_notebook_left), tab, TRUE);
			}
		}

		gtk_notebook_set_current_page(GTK_NOTEBOOK(debug_notebook_left), config_get_selected_tab_index());

		gtk_widget_show_all(hpaned);
	}
	else
	{
		gsize length;
		int i;
		int *tab_ids;

		gtk_paned_add2(GTK_PANED(hpaned), debug_notebook_right);
		g_object_unref(debug_notebook_right);

		tab_ids = config_get_right_tabs(&length);
		for (i = 0; i < length; i++)
		{
			GtkWidget *tab = tabs_get_tab((tab_id)tab_ids[i]);
			g_object_ref(tab);
			gtk_container_remove(GTK_CONTAINER(debug_notebook_left), tab);
			gtk_notebook_insert_page(GTK_NOTEBOOK(debug_notebook_right), tab, gtk_label_new(tabs_get_label(tab_ids[i])), i);
			g_object_unref(tab);
			gtk_notebook_set_tab_detachable(GTK_NOTEBOOK(debug_notebook_right), tab, TRUE);
				gtk_notebook_set_tab_reorderable(GTK_NOTEBOOK(debug_notebook_right), tab, TRUE);
		}

		gtk_notebook_set_current_page(GTK_NOTEBOOK(debug_notebook_left), config_get_left_selected_tab_index());
		gtk_notebook_set_current_page(GTK_NOTEBOOK(debug_notebook_right), config_get_right_selected_tab_index());

		gtk_widget_show_all(hpaned);
	}

	CONNECT_PAGE_SIGNALS();

	config_set_panel(CP_TABBED_MODE, (gpointer)&tabbed, 0);
}
