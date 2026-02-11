web_view_gtkhtml_extract_uri (EWebViewGtkHTML *web_view,
                              GdkEventButton *event,
                              GtkHTML *html)
{
	gchar *uri;

	if (event != NULL)
		uri = gtk_html_get_url_at (html, event->x, event->y);
	else
		uri = gtk_html_get_cursor_url (html);

	return uri;
}
