set_primary_output (CcDisplayPanel *self,
                    GnomeRROutputInfo *output)
{
  int i;
  GnomeRROutputInfo **outputs;

  outputs = gnome_rr_config_get_outputs (self->priv->current_configuration);
  for (i = 0; outputs[i] != NULL; ++i)
    gnome_rr_output_info_set_primary (outputs[i], outputs[i] == output);

  gtk_widget_queue_draw (WID ("self->priv->area"));

  refresh_unity_launcher_placement (self);
}
