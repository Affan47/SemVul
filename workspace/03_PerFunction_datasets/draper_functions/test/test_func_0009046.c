_e2_confdlg_clean (void)
{
	if (config_dialog != NULL)
	{
		printd (DEBUG, "config dialog widget destroy");
		app.cfgdlg_width = config_dialog->allocation.width;
		app.cfgdlg_height = config_dialog->allocation.height;
		gtk_widget_destroy (config_dialog);
		config_dialog = NULL;
	}

	g_hash_table_destroy (tree_view_buffer_hash);
}
