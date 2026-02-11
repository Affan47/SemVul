gw_notebook_managment_load_device_list ( GtkWindow *w) {
	GList *devices = NULL, *tmp = NULL;
	GtkCombo *cmb = NULL;
	gint result = -1;
	gchar *selected_device = NULL;
	gchar *text_utf8 = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		devices = gw_get_drives_list ( devices);

		if ( devices != NULL ) {
			cmb = gw_notebook_managment_get_combo_box_device ( w);

			if ( cmb != NULL ) {
				gtk_combo_set_popdown_strings ( cmb, devices);


				if ( (selected_device = gw_am_get_settings ( GW_VALUE_APP_DISK_SELECTED)) == NULL ) {
					selected_device = GW_VALUE_APP_DISK_SELECTED_DEFAULT;
				}

				if ( (tmp = g_list_find_custom ( devices, selected_device, (GCompareFunc)strcmp)) == NULL) {
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
					g_print ( "*** GW - %s (%d) :: %s() : select default device = %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, selected_device);
#endif

					tmp = g_list_first ( devices);
				} else {}


				g_strdup_to_gtk_text ( tmp->data, text_utf8);
				gtk_entry_set_text ( GTK_ENTRY ( cmb->entry), text_utf8);
				g_free ( text_utf8);

				if ( devices != NULL ) {
					g_list_foreach ( devices, (GFunc)g_free, NULL);
					g_list_free ( devices);
				}

				result = 0;
			}
		}
	}

	return result;
}
