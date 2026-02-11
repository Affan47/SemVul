panel_separator_load (PanelWidget *panel,
		      const char  *id,
		      GSettings   *settings)
{
	PanelSeparator *separator;

	separator = g_object_new (PANEL_TYPE_SEPARATOR, NULL);

	separator->priv->info = panel_applet_register (GTK_WIDGET (separator),
						       panel,
						       PANEL_OBJECT_SEPARATOR,
						       id, settings,
						       NULL, NULL
						       );

	if (!separator->priv->info) {
		gtk_widget_destroy (GTK_WIDGET (separator));
		return;
	}

	panel_widget_set_applet_expandable (panel, GTK_WIDGET (separator),
					    FALSE, TRUE);
	panel_widget_set_applet_size_constrained (panel,
						  GTK_WIDGET (separator), TRUE);
}
