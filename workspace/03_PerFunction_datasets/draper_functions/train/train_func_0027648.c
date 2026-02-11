setup_icon_chooser (PanelDItemEditor *dialog,
		    const char       *icon_name)
{
	char *buffer;

	if (!icon_name || icon_name[0] == '\0') {
		if (dialog->priv->type_directory) {
			buffer = g_strdup (PANEL_ICON_FOLDER);
		} else {
			buffer = g_strdup (PANEL_ICON_LAUNCHER);
		}
	} else {
		buffer = g_strdup (icon_name);
	}

	panel_icon_chooser_set_icon (PANEL_ICON_CHOOSER (dialog->priv->icon_chooser),
				     buffer);

	g_free (buffer);
}
