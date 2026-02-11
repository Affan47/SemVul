SendCB(GtkWidget * widget, gpointer data)
{
	PhoneEvent *e;
	gchar *buf = g_strdup(gtk_entry_get_text(GTK_ENTRY(displayEntry)));

	if (*buf == '\0') {
		g_free(buf);
		return;
	}

	e = g_malloc(sizeof(PhoneEvent));
	e->event = Event_SendDTMF;
	e->data = buf;
	GUI_InsertEvent(e);
}
