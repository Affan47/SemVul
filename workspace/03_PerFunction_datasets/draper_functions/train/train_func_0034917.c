gkrellm_remove_plugin_config_page(GkrellmMonitor *mon)
	{
	GtkTreePath		*path;
	GtkTreeIter		iter;
	GList			*list;
	GkrellmMonitor	*tmon;

	if (mon->privat->config_page > 0)
		{
		path = gtk_tree_row_reference_get_path(mon->privat->row_reference);
		gtk_tree_model_get_iter(GTK_TREE_MODEL(model), &iter, path);
		gtk_tree_store_remove(model, &iter);

		gtk_notebook_remove_page(config_notebook, mon->privat->config_page);


		for (list = gkrellm_monitor_list; list; list = list->next)
			{
			tmon = (GkrellmMonitor *) list->data;
			if (mon->privat->config_page >= tmon->privat->config_page)
				continue;
			tmon->privat->config_page -= 1;
			gkrellm_debug(DEBUG_GUI, "config_page %d: %s\n",
						tmon->privat->config_page,  tmon->name);
			}
		}
	mon->privat->config_page = -1;
	}
