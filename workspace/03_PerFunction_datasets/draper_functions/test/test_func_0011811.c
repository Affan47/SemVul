text_dump_page(GtkWidget *widget,gpointer *data){

	gint page, offset;
	const gchar *p;
	gchar *text;
	gchar *utf_text;
	GtkTextIter iter;
	GtkTextIter start, end;

	LOG(LOG_DEBUG, "IN : text_dump_page()");

	p = gtk_entry_get_text(GTK_ENTRY(entry_text_page));
	if(strlen(p) == 0)
		return;
	page = strtol(p, NULL, 16);

	p = gtk_entry_get_text(GTK_ENTRY(entry_text_offset));
	if(strlen(p) == 0)
		return;
	offset = strtol(p, NULL, 16);

	if(current_result == NULL)
		return;

	text = ebook_get_text(current_result->data.eb.book_info,
			      page,
			      offset);
	if(text == NULL)
	{
		return;
	}

	gtk_text_buffer_get_bounds (text_buffer, &start, &end);
	gtk_text_buffer_delete(text_buffer, &start, &end);

	gtk_text_buffer_get_start_iter (text_buffer, &iter);
	utf_text = iconv_convert("euc-jp", "utf-8", text);
	gtk_text_buffer_insert (text_buffer, &iter,
				utf_text, -1);
	free(text);
	free(utf_text);

	LOG(LOG_DEBUG, "OUT : text_dump_page()");

}
