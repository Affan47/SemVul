web_view_gtkhtml_request_check_for_error (EWebViewGtkHTMLRequest *request,
                                          GError *error)
{
	GtkHTML *html;
	GtkHTMLStream *stream;

	if (error == NULL)
		return FALSE;

	if (g_error_matches (error, G_IO_ERROR, G_IO_ERROR_NOT_SUPPORTED)) {

		g_error_free (error);
		return TRUE;
	}


	html = GTK_HTML (request->web_view);
	stream = request->output_stream;

	gtk_html_end (html, stream, GTK_HTML_STREAM_ERROR);
	web_view_gtkhtml_request_free (request);
	g_error_free (error);

	return TRUE;
}
