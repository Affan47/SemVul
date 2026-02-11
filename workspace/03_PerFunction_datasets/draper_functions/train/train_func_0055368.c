cc_region_panel_init (CcRegionPanel * self)
{
	CcRegionPanelPrivate *priv;
	GtkWidget *prefs_widget;
	GError *error = NULL;

	priv = self->priv = REGION_PANEL_PRIVATE (self);

	priv->builder = gtk_builder_new ();

	gtk_builder_add_from_file (priv->builder,
				   GNOMECC_UI_DIR "/gnome-region-panel.ui",
				   &error);
	if (error != NULL) {
		g_warning ("Error loading UI file: %s", error->message);
		g_error_free (error);
		return;
	}

	prefs_widget = (GtkWidget *) gtk_builder_get_object (priv->builder,
							     "region_notebook");
	gtk_widget_set_size_request (GTK_WIDGET (prefs_widget), -1, 400);

	gtk_widget_reparent (prefs_widget, GTK_WIDGET (self));

        setup_input_tabs (priv->builder, self);
	setup_language (priv->builder);
	setup_formats (priv->builder);
	setup_system (priv->builder);
}
