format_ablock(GtkHex *gh, gchar *out, guint start, guint end) {
	int i, j;
	guchar c;

	for(i = start, j = 0; i < end; i++, j++) {
		c = gtk_hex_get_byte(gh, i);
		if(is_displayable(c))
			out[j] = c;
		else
			out[j] = '.';
	}

	return end - start;
}
