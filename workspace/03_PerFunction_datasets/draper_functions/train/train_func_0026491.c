gw_settings_window_box_tree_select_row ( GtkCTree *ctree, GList *node, gint column, GtkWindow *w)
{
	GtkNotebook *notebook_settings = NULL;
	GWSettingsModule *module = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( ctree != NULL )
	{
		notebook_settings = gw_settings_window_box_get_notebook ( w);
		module = gtk_ctree_node_get_row_data ( ctree, GTK_CTREE_NODE ( node));

		if ( module != NULL )
		{
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
		g_print ( "*** GW - %s (%d) :: %s() : selected settings module is %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, module->name);
#endif


			gtk_notebook_set_page ( notebook_settings, gtk_notebook_page_num ( notebook_settings, GTK_WIDGET ( module->page)));
		}
	}

	return;
}
