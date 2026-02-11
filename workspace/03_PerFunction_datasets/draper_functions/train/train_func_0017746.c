insert_text_cb (GtkTextBuffer *textbuffer, GtkTextIter *location,
    gchar *text, gint len, gpointer user_data)
{
	GtkWidget * undo, * undomenu;
	Ebook * ebook;
	UData * ud;

	ebook = (Ebook *)user_data;
	undo = GTK_WIDGET(gtk_builder_get_object (ebook->builder, "undo_button"));
	undomenu = GTK_WIDGET(gtk_builder_get_object (ebook->builder, "undomenuitem"));
	ud = g_new0(UData, 1);
	ud->str = g_strdup(text);
	ud->add = TRUE;
	ud->start = gtk_text_iter_get_offset(location);
	ud->len = strlen (text);
	ud->end = gtk_text_iter_get_offset(location) + (gint)len;
	g_trash_stack_push (&ebook->undo_stack, ud);
	gtk_widget_set_sensitive (undo, TRUE);
	gtk_widget_set_sensitive (undomenu, TRUE);
}
