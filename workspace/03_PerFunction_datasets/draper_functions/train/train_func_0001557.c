gw_menu_file_exit_save_file_ok ( GtkWidget *bt, GtkWindow *dg) {
	GWDBCatalog *catalog = NULL;
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	gtk_widget_destroy ( GTK_WIDGET ( dg));


	if ( gw_helper_db_catalog_is_new ( catalog)) {


		gw_file_selection_box_create ( _( "Save as catalog"), gw_helper_db_catalog_get_usefull_name ( catalog), (GtkSignalFunc)gw_menu_file_exit_saveas_file_selection_ok, NULL);
	} else {

		gw_menu_file_save_click ( NULL, NULL);
		gw_menu_file_exit ( );
	}

	result = TRUE;

	return result;
}
