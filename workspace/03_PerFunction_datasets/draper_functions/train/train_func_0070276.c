gw_mail_window_box_get_bcc ( GtkWindow *w)
{
	GtkEntry *entry = NULL;
	gchar *text = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		if ( (entry = GTK_ENTRY ( gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_MAIL_WINDOW_BOX_BCC_ENTRY))) != NULL )
		{
			g_strdup_from_gtk_text ( gtk_entry_get_text ( entry), text);
		}

#ifdef GW_DEBUG_GUI_COMPONENT
		g_print ( "*** GW - %s (%d) :: %s() : bcc field = %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, text);
#endif
	}

	return text;
}
