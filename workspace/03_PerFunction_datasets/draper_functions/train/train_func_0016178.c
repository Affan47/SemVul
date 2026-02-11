totem_properties_view_init (TotemPropertiesView *props)
{
	GError *err = NULL;

	props->priv = g_new0 (TotemPropertiesViewPriv, 1);

	props->priv->vbox = bacon_video_widget_properties_new ();
	gtk_grid_attach (GTK_GRID (props), props->priv->vbox, 0, 0, 1, 1);
	gtk_widget_show (GTK_WIDGET (props));

	props->priv->props = BACON_VIDEO_WIDGET_PROPERTIES (props->priv->vbox);

	props->priv->disco = gst_discoverer_new (GST_SECOND * 60, &err);
	if (props->priv->disco == NULL) {
		g_warning ("Could not create discoverer object: %s", err->message);
		g_error_free (err);
		return;
	}
	g_signal_connect (props->priv->disco, "discovered",
			  G_CALLBACK (discovered_cb), props);
}
