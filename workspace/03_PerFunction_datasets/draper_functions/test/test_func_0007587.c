buffer_to_pdf (Ebook * ebook)
{
	GtkTextBuffer * buffer;
	GtkTextIter start, end;
	Pqueue queue;
	gchar * size, *editor_font;


	queue.ebook = ebook;
	queue.pos = 0;
	queue.page_count = 1;
	queue.width = 8.3 * POINTS;
	queue.height = 11.7 * POINTS;
	queue.page_height = 40.0;
	g_return_if_fail (ebook);
	g_return_if_fail (ebook->filename);
	size = gconf_client_get_string (ebook->client, ebook->paper_size.key, NULL);
	buffer = GTK_TEXT_BUFFER(gtk_builder_get_object (ebook->builder, "textbuffer1"));
	queue.progressbar = GTK_PROGRESS_BAR(gtk_builder_get_object (ebook->builder, "progressbar"));
	queue.statusbar = GTK_STATUSBAR(gtk_builder_get_object (ebook->builder, "statusbar"));
	gtk_text_buffer_get_bounds (buffer, &start, &end);
	queue.text = g_strdup(gtk_text_buffer_get_text (buffer, &start, &end, TRUE));
	editor_font = gconf_client_get_string(ebook->client, ebook->editor_font.key, NULL);
	if (0 == g_strcmp0 (size, "A5"))
	{
		queue.width = a5_width * POINTS;
		queue.height = a5_height * POINTS;
	}
	if (0 == g_strcmp0 (size, "B5"))
	{
		queue.width = b5_width * POINTS;
		queue.height = b5_height * POINTS;
	}
	queue.surface = cairo_pdf_surface_create (ebook->filename, queue.width, queue.height);
	queue.cr = cairo_create (queue.surface);
	queue.context = pango_cairo_create_context (queue.cr);

	queue.desc = pango_font_description_from_string (editor_font);
	queue.layout = make_new_page (queue.context, queue.desc, queue.height, queue.width);
	pango_layout_set_text (queue.layout, queue.text, -1);
	cairo_move_to (queue.cr, SIDE_MARGIN / 2, EDGE_MARGIN / 2);
	gtk_progress_bar_set_fraction (queue.progressbar, 0.0);
	queue.lines_per_page = pango_layout_get_line_count (queue.layout);
	queue.iter = pango_layout_get_iter (queue.layout);
	create_pages (&queue);
}
