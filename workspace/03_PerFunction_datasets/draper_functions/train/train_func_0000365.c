txv_text_append_with_color(GtkWidget *wid, const gchar *text, gsize length, const GdkColor *color)
{
	TxvInfo		*txi;
	GtkTextIter	start, end;
	gchar		tname[32];
	gint		pos;
	GtkTextTagTable	*ttab;
	GtkTextTag	*tag;

	if(color == NULL)
	{
		txv_text_append(wid, text, length);
		return;
	}
	if((wid == NULL) || ((txi = g_object_get_data(G_OBJECT(wid), "user")) == NULL) || length < 1)
		return;
	pos = gtk_text_buffer_get_char_count(GTK_TEXT_BUFFER(txi->buffer));
	do_text_append(txi, text, length);
	gtk_text_buffer_get_iter_at_offset(GTK_TEXT_BUFFER(txi->buffer), &start, pos);
	gtk_text_buffer_get_end_iter(GTK_TEXT_BUFFER(txi->buffer), &end);


	g_snprintf(tname, sizeof tname, "txv-%04x%04x%04x", color->red, color->green, color->blue);

	ttab = gtk_text_buffer_get_tag_table(GTK_TEXT_BUFFER(txi->buffer));
	if((tag = gtk_text_tag_table_lookup(ttab, tname)) == NULL)
		tag = gtk_text_buffer_create_tag(GTK_TEXT_BUFFER(txi->buffer), tname, "foreground-gdk", color, NULL);
	gtk_text_buffer_apply_tag(GTK_TEXT_BUFFER(txi->buffer), tag, &start, &end);
}
