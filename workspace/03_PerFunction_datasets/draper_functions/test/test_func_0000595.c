nautilus_desktop_background_set_image_uri (NautilusDesktopBackground *self,
                                           const char *image_uri)
{
	char *filename;

	if (image_uri != NULL) {
		filename = g_filename_from_uri (image_uri, NULL, NULL);
	}
	else {
		filename = NULL;
	}

	gnome_bg_set_filename (self->details->bg, filename);

	g_free (filename);
}
