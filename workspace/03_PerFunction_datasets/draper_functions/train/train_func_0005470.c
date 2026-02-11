gtk_hotkey_info_finalize (GObject * obj)
{
	GtkHotkeyInfo			*self;
	GtkHotkeyInfoPrivate	*priv;

	self = GTK_HOTKEY_INFO (obj);
	priv = self->priv;

	if (priv->app_id)
		g_free (priv->app_id);
	if (priv->key_id)
		g_free (priv->key_id);
	if (priv->app_info)
		g_object_unref (priv->app_info);
	if (priv->signature)
		g_free (priv->signature);
	if (priv->description)
		g_free (priv->description);
	if (GTK_HOTKEY_IS_LISTENER (priv->listener))
		g_object_unref (priv->listener);

	G_OBJECT_CLASS (gtk_hotkey_info_parent_class)->finalize (obj);
}
