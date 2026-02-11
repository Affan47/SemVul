show_source (GtrCodeViewPlugin * plugin, const gchar * path, gint line)
{
  gboolean use_editor;

  use_editor = g_settings_get_boolean (plugin->priv->settings,
                                       GTR_SETTINGS_USE_EDITOR);

  if (use_editor)
    {
      gchar *program_cmd;
      gchar *line_cmd;


      program_cmd = g_settings_get_string (plugin->priv->settings,
                                           GTR_SETTINGS_PROGRAM_CMD);


      line_cmd = g_settings_get_string (plugin->priv->settings,
                                        GTR_SETTINGS_LINE_CMD);

      show_in_editor (program_cmd, line_cmd, path, line);

      g_free (program_cmd);
      g_free (line_cmd);
    }
  else
    gtr_show_viewer (plugin->priv->window, path, line);
}
