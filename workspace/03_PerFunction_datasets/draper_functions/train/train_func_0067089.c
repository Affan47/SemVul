settings_update_resolution (ClutterSettings *self)
{
  CLUTTER_NOTE (BACKEND, "New resolution: %.2f", self->resolution);

  if (self->backend != NULL)
    g_signal_emit_by_name (self->backend, "resolution-changed");
}
