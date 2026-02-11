gw_mail_window_box_get_file_path ( GtkWindow *w)
{
	GtkCheckButton *chk_button = NULL;
	gchar *text = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		chk_button = gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_MAIL_WINDOW_BOX_ATTACH_FILE_CHK);

#ifdef GW_DEBUG_GUI_COMPONENT
		g_print ( "*** GW - %s (%d) :: %s() : file path = %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, text);
#endif

		if ( chk_button != NULL )
		{
			gtk_label_get ( GTK_LABEL ( GTK_BIN ( GTK_BUTTON ( chk_button))->child), &text);
			g_strdup_from_gtk_text ( text, text);
		}
	}

	return text;
}
