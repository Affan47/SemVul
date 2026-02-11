accessible_gtk_hex_get_character_at_offset (AtkText *text,
					    gint offset)
{

	GtkWidget *widget;
	GtkHex *gtk_hex ;
	gchar str[2];
	gunichar c = '.';

	widget = gtk_accessible_get_widget (GTK_ACCESSIBLE (text));
	gtk_hex = GTK_HEX (widget);

	if (gtk_hex->active_view == VIEW_ASCII) {
		format_ablock (gtk_hex, str, offset, offset+1);
		c = g_utf8_get_char_validated (str, 1);
	}
	if (gtk_hex->active_view == VIEW_HEX) {
		format_xbyte (gtk_hex, offset, str);
		c = g_utf8_get_char_validated (str, 2);
	}

	return c;
}
