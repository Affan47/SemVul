search_search (session * sess, const gchar *text)
{
	gtk_xtext_search_flags flags;
	textentry *last;
	GError *err = NULL;

	flags = ((prefs.hex_text_search_case_match == 1? case_match: 0) |
				(prefs.hex_text_search_backward == 1? backward: 0) |
				(prefs.hex_text_search_highlight_all == 1? highlight: 0) |
				(prefs.hex_text_search_follow == 1? follow: 0) |
				(prefs.hex_text_search_regexp == 1? regexp: 0));
	if (!is_session (sess))
	{
		fe_message (_("The window you opened this Search "
						"for doesn't exist anymore."), FE_MSG_ERROR);
		return;
	}

	last = gtk_xtext_search (GTK_XTEXT (sess->gui->xtext), text, flags, &err);
	if (text == NULL || text[0] == 0)
	{
		return;
	}
	if (err)
	{
		fe_message (_(err->message), FE_MSG_ERROR);
		g_error_free (err);
	}
	else if (!last)
	{
		gtk_entry_set_icon_from_stock (GTK_ENTRY (searchentry), GTK_ENTRY_ICON_SECONDARY, GTK_STOCK_DIALOG_ERROR);
	}
	else
	{
		gtk_entry_set_icon_from_stock (GTK_ENTRY (searchentry), GTK_ENTRY_ICON_SECONDARY, NULL);
	}
}
