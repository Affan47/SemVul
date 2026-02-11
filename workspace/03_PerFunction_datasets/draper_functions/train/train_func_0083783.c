line_mark_activated (GtkSourceGutter *gutter,
                     GtkTextIter     *iter,
                     GdkEventButton  *event,
                     GtkSourceView   *view)
{
	GtkSourceBuffer *buffer;
	GSList *mark_list;
	const gchar *mark_type;

	mark_type = event->button == 1 ? MARK_TYPE_1 : MARK_TYPE_2;

	buffer = GTK_SOURCE_BUFFER (gtk_text_view_get_buffer (GTK_TEXT_VIEW (view)));


	mark_list = gtk_source_buffer_get_source_marks_at_line (buffer,
								gtk_text_iter_get_line (iter),
								mark_type);

	if (mark_list != NULL)
	{

		gtk_text_buffer_delete_mark (GTK_TEXT_BUFFER (buffer),
					     GTK_TEXT_MARK (mark_list->data));
	}
	else
	{

		gtk_source_buffer_create_source_mark (buffer,
						      NULL,
						      mark_type,
						      iter);
	}

	g_slist_free (mark_list);
}
