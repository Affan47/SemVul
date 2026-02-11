panel_ditem_editor_dispose (GObject *object)
{
	PanelDItemEditor *dialog;

	dialog = PANEL_DITEM_EDITOR (object);


	if (dialog->priv->save_timeout) {
		g_source_remove (dialog->priv->save_timeout);
		dialog->priv->save_timeout = 0;
		panel_ditem_editor_save (dialog, FALSE);
	}


	if (dialog->priv->free_key_file && dialog->priv->key_file != NULL)
		g_key_file_free (dialog->priv->key_file);
	dialog->priv->key_file = NULL;

	if (dialog->priv->revert_key_file != NULL)
		g_key_file_free (dialog->priv->revert_key_file);
	dialog->priv->revert_key_file = NULL;

	if (dialog->priv->uri != NULL)
		g_free (dialog->priv->uri);
	dialog->priv->uri = NULL;

	G_OBJECT_CLASS (panel_ditem_editor_parent_class)->dispose (object);
}
