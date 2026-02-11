edit_custom_shortcut (CcKeyboardItem *item)
{
  gint result;
  gboolean ret;
  GSettings *settings;

  settings = g_settings_new_with_path (item->schema, item->gsettings_path);

  g_settings_bind (settings, "name",
                   G_OBJECT (custom_shortcut_name_entry), "text",
                   G_SETTINGS_BIND_DEFAULT);
  gtk_widget_grab_focus (custom_shortcut_name_entry);

  g_settings_bind (settings, "command",
                   G_OBJECT (custom_shortcut_command_entry), "text",
                   G_SETTINGS_BIND_DEFAULT);

  g_settings_delay (settings);

  gtk_window_present (GTK_WINDOW (custom_shortcut_dialog));
  result = gtk_dialog_run (GTK_DIALOG (custom_shortcut_dialog));
  switch (result)
    {
    case GTK_RESPONSE_OK:
      g_settings_apply (settings);
      ret = TRUE;
      break;
    default:
      g_settings_revert (settings);
      ret = FALSE;
      break;
    }

  g_settings_unbind (G_OBJECT (custom_shortcut_name_entry), "text");
  g_settings_unbind (G_OBJECT (custom_shortcut_command_entry), "text");

  g_object_unref (settings);

  gtk_widget_hide (custom_shortcut_dialog);

  return ret;
}
