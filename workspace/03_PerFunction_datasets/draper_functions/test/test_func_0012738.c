dispose (GObject *object)
{
	DhSettings *self = DH_SETTINGS (object);
        g_clear_object (&self->priv->settings_desktop_interface);
        g_clear_object (&self->priv->settings_fonts);
	g_clear_object (&self->priv->settings_window);
        g_clear_object (&self->priv->settings_contents);
        g_clear_object (&self->priv->settings_paned);
        g_clear_object (&self->priv->settings_search_notebook);
        g_clear_object (&self->priv->settings_assistant);

	G_OBJECT_CLASS (dh_settings_parent_class)->dispose (object);
}
