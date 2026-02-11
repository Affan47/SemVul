set_bitrate (TotemPropertiesView    *props,
	     guint                   bitrate,
	     const char             *widget)
{
	char *string;

	if (!bitrate) {
		bacon_video_widget_properties_set_label (props->priv->props,
							 widget,
							 C_("Stream bit rate", "N/A"));
		return;
	}
	string = g_strdup_printf (_("%d kbps"), bitrate / 1000);
	bacon_video_widget_properties_set_label (props->priv->props,
						 widget,
						 string);
	g_free (string);
}
