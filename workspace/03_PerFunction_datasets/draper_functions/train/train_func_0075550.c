pdf_viewer_button_rotate_left_cb(GtkButton *button, PdfViewer *viewer)
{
	if (viewer->rotate == 0) {
		viewer->rotate = 360;
	}

	viewer->rotate = abs(viewer->rotate -(gint) ROTATION);
	pdf_viewer_update((MimeViewer *)viewer, FALSE,
		gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(viewer->cur_page)));
}
