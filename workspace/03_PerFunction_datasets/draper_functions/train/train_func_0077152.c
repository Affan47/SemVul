cm_menu_item_new_label_from_url(gchar *url)
{
	gint len = strlen(url);
	if (len > MAX_MENU_LABEL_LENGTH) {
		g_message("Refusing a %d bytes string as menu label\n", len);
		url[64] = '\0', url[63] = url[62] = url[61] = '.', url[60] = ' ';
		GtkWidget *newlabel = gtk_menu_item_new_with_label(url);
		gtk_widget_set_tooltip_markup(GTK_WIDGET(newlabel),
			_("<span><b>Warning:</b> This URL was too long for displaying and\n"
			"has been truncated for safety. This message could be\n"
			"corrupted, malformed or part of some DoS attempt.</span>"));
		return newlabel;
	}

	return gtk_menu_item_new_with_label(url);
}
