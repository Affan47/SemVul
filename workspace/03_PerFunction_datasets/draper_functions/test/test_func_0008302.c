change_menu_label (GladeWindow *window,
		   const gchar *path,
		   const gchar *action_label,
		   const gchar *action_description)
{
	GtkBin *bin;
	GtkLabel *label;
	gchar *text;
	gchar *tmp_text;

	g_assert (GLADE_IS_WINDOW (window));
	g_return_if_fail (path != NULL);
	g_return_if_fail (action_label != NULL);

	bin = GTK_BIN (gtk_ui_manager_get_widget (window->priv->ui, path));
	label = GTK_LABEL (gtk_bin_get_child (bin));

	if (action_description == NULL)
		text = g_strdup (action_label);
	else
	{
		tmp_text = escape_underscores (action_description, -1);
		text = g_strdup_printf ("%s: %s", action_label, tmp_text);
		g_free (tmp_text);
	}

	gtk_label_set_text_with_mnemonic (label, text);

	g_free (text);
}
