text_view_append(GtkWidget *view, gchar *s)
	{
	GtkTextIter		iter;
	GtkTextBuffer	*buffer;

	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));
	gtk_text_buffer_get_end_iter(buffer, &iter);


	if (strncmp(s, "<b>", 3) == 0)
		gtk_text_buffer_insert_with_tags_by_name (buffer, &iter,
					s + 3, -1, "bold", NULL);
	else if (strncmp(s, "<i>", 3) == 0)
		gtk_text_buffer_insert_with_tags_by_name (buffer, &iter,
					s + 3, -1, "italic", NULL);
	else if (strncmp(s, "<h>", 3) == 0)
		gtk_text_buffer_insert_with_tags_by_name (buffer, &iter,
					s + 3, -1, "heading", NULL);
	else if (strncmp(s, "<c>", 3) == 0)
		gtk_text_buffer_insert_with_tags_by_name (buffer, &iter,
					s + 3, -1, "center", NULL);
	else if (strncmp(s, "<ul>", 4) == 0)
		gtk_text_buffer_insert_with_tags_by_name (buffer, &iter,
					s + 4, -1, "underline", NULL);
	else
		gtk_text_buffer_insert(buffer, &iter, s, -1);
	}
