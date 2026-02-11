undo_cb (GtkWidget * widget, gpointer user_data)
{
	GtkWidget * redo, * undo, * redomenu, * undomenu;
	GtkTextBuffer * buffer;
	GtkTextIter start, end;
	Ebook * ebook;
	UData * ud;

	ebook = (Ebook *)user_data;
	buffer = GTK_TEXT_BUFFER(gtk_builder_get_object (ebook->builder, "textbuffer1"));
	redo = GTK_WIDGET(gtk_builder_get_object (ebook->builder, "redo_button"));
	undo = GTK_WIDGET(gtk_builder_get_object (ebook->builder, "undo_button"));
	redomenu = GTK_WIDGET(gtk_builder_get_object (ebook->builder, "redomenuitem"));
	undomenu = GTK_WIDGET(gtk_builder_get_object (ebook->builder, "undomenuitem"));

	ud = g_trash_stack_pop (&ebook->undo_stack);
	g_return_if_fail (ud);
	g_trash_stack_push (&ebook->redo_stack, ud);
	if (ud->add)
	{
		gtk_text_buffer_get_iter_at_offset (buffer, &start, ud->start);
		gtk_text_buffer_get_iter_at_offset (buffer, &end, ud->end);
		gtk_text_buffer_delete (buffer, &start, &end);
		g_trash_stack_pop (&ebook->undo_stack);
	}
	else
	{
		gtk_text_buffer_get_iter_at_offset (buffer, &start, ud->start);
		gtk_text_buffer_insert (buffer, &start, ud->str, ud->len);
		g_trash_stack_pop (&ebook->undo_stack);
	}
	gtk_widget_set_sensitive (redo, TRUE);
	gtk_widget_set_sensitive (redomenu, TRUE);
	if (!ebook->undo_stack)
	{
		gtk_widget_set_sensitive (undo, FALSE);
		gtk_widget_set_sensitive (undomenu, FALSE);
	}
}
