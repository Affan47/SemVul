on_launcher_placement_combo_changed (GtkComboBox *combo, CcDisplayPanel *self)
{
  gint active = gtk_combo_box_get_active (combo);
  gint i;
  gint index_on_combo = 0;

  if (active < 0)
    return;
  gint value = 0;
  gboolean on_all_monitors = switcher_set_to_launcher_on_all_monitors (self);

  if (!on_all_monitors) {
    value = 1;

    GnomeRROutputInfo **outputs = gnome_rr_config_get_outputs (self->priv->current_configuration);

    for (i = 0; outputs[i] != NULL; ++i)
      {
        GnomeRROutputInfo *output = outputs[i];
        if (!gnome_rr_output_info_is_active (output))
          continue;

        if ((active == index_on_combo) && !gnome_rr_output_info_get_primary (output))
          {
            set_primary_output (self, output);
            break;
          }
        index_on_combo++;
      }
  }


  if (self->priv->unity_settings)
    g_settings_set_int (self->priv->unity_settings, UNITY_LAUNCHER_ALL_MONITORS_KEY, value);

  if (self->priv->unity2d_settings_launcher)
    g_settings_set_boolean (self->priv->unity2d_settings_launcher, "only-one-launcher", !on_all_monitors);
}
