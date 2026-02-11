impl_deactivate (PeasActivatable *plugin)
{
	TotemVimeoPlugin *pi = TOTEM_VIMEO_PLUGIN (plugin);

	if (pi->priv->signal_id) {
		g_signal_handler_disconnect (pi->priv->totem, pi->priv->signal_id);
		pi->priv->signal_id = 0;
	}

	if (pi->priv->totem) {
		g_object_unref (pi->priv->totem);
		pi->priv->totem = NULL;
	}
}
