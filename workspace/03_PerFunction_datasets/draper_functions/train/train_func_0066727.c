gtk_file_chooser_preview_init (GtkFileChooserPreview *preview)
{
	preview->priv = g_new0 (GtkFileChooserPreviewPrivateData, 1);
	preview->priv->thumb_factory = gnome_desktop_thumbnail_factory_new (GNOME_DESKTOP_THUMBNAIL_SIZE_NORMAL);
	preview->priv->uri = NULL;
}
