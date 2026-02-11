gw_menu_options_settings_click ( GtkMenuItem *m, GtkWindow *w)
{
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		gw_settings_window_box_create ( w);

		result = TRUE;
	}

	return result;
}
