bacon_video_widget_properties_set_has_type (BaconVideoWidgetProperties *props,
					    gboolean                    has_video,
					    gboolean                    has_audio)
{
	GtkWidget *item;

	g_return_if_fail (props != NULL);
	g_return_if_fail (BACON_IS_VIDEO_WIDGET_PROPERTIES (props));


	item = GTK_WIDGET (gtk_builder_get_object (props->priv->xml, "video"));
	gtk_widget_set_sensitive (item, has_video);
	item = GTK_WIDGET (gtk_builder_get_object (props->priv->xml, "video_vbox"));
	gtk_widget_set_visible (item, has_video);


	item = GTK_WIDGET (gtk_builder_get_object (props->priv->xml, "audio"));
	gtk_widget_set_sensitive (item, has_audio);
}
