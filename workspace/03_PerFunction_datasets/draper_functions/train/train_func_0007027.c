e_web_view_gtkhtml_extract_uri (EWebViewGtkHTML *web_view,
                                GdkEventButton *event,
                                GtkHTML *frame)
{
	EWebViewGtkHTMLClass *class;

	g_return_val_if_fail (E_IS_WEB_VIEW_GTKHTML (web_view), NULL);

	if (frame == NULL)
		frame = GTK_HTML (web_view);

	class = E_WEB_VIEW_GTKHTML_GET_CLASS (web_view);
	g_return_val_if_fail (class->extract_uri != NULL, NULL);

	return class->extract_uri (web_view, event, frame);
}
