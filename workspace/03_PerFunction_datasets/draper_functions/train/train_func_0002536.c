list_image_free(gpointer, gpointer value, gpointer) {
	ListImage *list_image = static_cast<ListImage *>(value);
	if (list_image->pixbuf)
		g_object_unref(list_image->pixbuf);
	g_free(list_image);
}
