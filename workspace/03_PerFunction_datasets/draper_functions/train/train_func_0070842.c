spin_cb (GtkSpinButton *widget, const gchar *key)
{
  xine_cfg_entry_t entry;
  int value;

  if (update_lock)
    return;

  logprintf ("preferences: spin cb for key %s\n", key);

  value = gtk_spin_button_get_value_as_int (widget);
  if (!xine_config_lookup_entry (xine, key, &entry) ||
      entry.num_value == value)
    return;

  logprintf ("preferences: updating entry to %d\n", value);
  entry.num_value = value;
  xine_config_update_entry (xine, &entry);
}
