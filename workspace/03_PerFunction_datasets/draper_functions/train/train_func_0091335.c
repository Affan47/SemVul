rebuild_on_off_radios (CcDisplayPanel *self)
{
  gboolean sensitive;
  gboolean on_active;

  g_signal_handlers_block_by_func (self->priv->monitor_switch, G_CALLBACK (monitor_switch_active_cb), self);

  sensitive = FALSE;
  on_active = FALSE;

  if (!gnome_rr_config_get_clone (self->priv->current_configuration) && self->priv->current_output)
    {
      if (count_active_outputs (self) > 1 || !gnome_rr_output_info_is_active (self->priv->current_output))
        sensitive = TRUE;
      else
        sensitive = FALSE;

      on_active = gnome_rr_output_info_is_active (self->priv->current_output);
    }

  gtk_widget_set_sensitive (self->priv->monitor_switch, sensitive);

  gtk_switch_set_active (GTK_SWITCH (self->priv->monitor_switch), on_active);

  g_signal_handlers_unblock_by_func (self->priv->monitor_switch, G_CALLBACK (monitor_switch_active_cb), self);
}
