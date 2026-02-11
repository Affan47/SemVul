apply_entry_value(GtkEntry *entry, gint signal_id)
{
  const char * key = get_preferences_key(G_OBJECT(entry));
  ProfileValue *value = get_current_profile_value(key);
  g_signal_handler_block(entry, signal_id);
  gtk_entry_set_text(entry, value == NULL ? "" : value->get_string_value());
  g_signal_handler_unblock(entry, signal_id);

  GtkToggleButton *toggle_button = GTK_TOGGLE_BUTTON(g_object_get_data(G_OBJECT(entry), DATA_KEY_CHECK_BUTTON));
  gtk_toggle_button_set_active(toggle_button, _current_profile->contains_key(key));
}
