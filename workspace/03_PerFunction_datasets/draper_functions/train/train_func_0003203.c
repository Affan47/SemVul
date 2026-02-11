__column_toggled_enabled(GtkCellRendererToggle *renderer,
										char *path,
										gpointer store)
{
	GtkTreeIter iter;
	if(gtk_tree_model_get_iter_from_string(GTK_TREE_MODEL(store), &iter, path))
	{
		gmpcPluginParent *plug;
		gtk_tree_model_get(GTK_TREE_MODEL(store), &iter, 0, &plug, -1);
		if(plug)
		{
			gboolean state = !gtk_cell_renderer_toggle_get_active(renderer);
			gmpc_plugin_set_enabled(plug,state);
			preferences_window_update();
		}
	}
}
