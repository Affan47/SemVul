revert_item_cb (GtkWidget *w, gpointer key)
{
  xine_cfg_entry_t entry;
  xine_config_lookup_entry (xine, key, &entry);
  if (entry.type == XINE_CONFIG_TYPE_STRING)
    entry.str_value = g_object_get_data ((GObject *) w, "revert");
  else
    entry.num_value = (int) (intptr_t) g_object_get_data ((GObject *) w, "revert");
  preferences_update_entry (&entry);
}
