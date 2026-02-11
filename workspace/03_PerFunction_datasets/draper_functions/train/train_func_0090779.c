fancy_scroll_page(MimeViewer *_viewer, gboolean up)
{
	FancyViewer *viewer = (FancyViewer *)_viewer;
	GtkAdjustment *vadj = gtk_scrolled_window_get_vadjustment(
					GTK_SCROLLED_WINDOW(viewer->scrollwin));

	if (viewer->view == NULL)
		return FALSE;

	return gtkutils_scroll_page(GTK_WIDGET(viewer->view), vadj, up);
}
