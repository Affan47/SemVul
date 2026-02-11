evt_dtooltip_changed(GtkWidget *wid, gpointer user)
{
	P_Buttons	*page = user;
	Button		*but;
	const gchar	*text;

	if((page != NULL) && (page->button != NULL) && ((but = btn_button_get(page->button)) != NULL))
	{
		if((text = gtk_entry_get_text(GTK_ENTRY(wid))) != NULL)
		{
			btn_button_set_tooltip(but, text);
			page->modified = TRUE;
		}
	}

	return TRUE;
}
