nemo_navigation_state_set_master (NemoNavigationState *self,
				      GtkActionGroup *master)
{
	if (self->priv->master != master) {
		clear_bindings (self);

		g_clear_object (&self->priv->master);
		self->priv->master = g_object_ref (master);

		update_bindings (self);

		g_object_notify_by_pspec (G_OBJECT (self), properties[PROP_MASTER]);
	}
}
