gtk_libvlc_media_add_option (GtkLibvlcMedia* media, gchar* option)
{
	g_return_if_fail(media != NULL);
	g_return_if_fail(GTK_IS_LIBVLC_MEDIA(media));
	g_return_if_fail(option != NULL);

	GtkLibvlcMediaPrivate* priv;

	priv = GTK_LIBVLC_MEDIA_PRIVATE(media);

	gchar *options[2];
	options[0] = option;
	options[1] = NULL;

	gtk_libvlc_media_add_options (media, options);
}
