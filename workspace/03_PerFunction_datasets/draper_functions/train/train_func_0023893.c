gdict_window_set_source_name (GdictWindow *window,
			      const gchar *source_name)
{
  GdictContext *context;

  if (window->source_name && source_name &&
      strcmp (window->source_name, source_name) == 0)
    return;

  g_free (window->source_name);

  if (source_name != NULL && *source_name != '\0')
    window->source_name = g_strdup (source_name);
  else
    window->source_name = g_settings_get_string (window->settings, GDICT_SETTINGS_SOURCE_KEY);

  context = get_context_from_loader (window);
  gdict_window_set_context (window, context);

  if (window->source_chooser)
    gdict_source_chooser_set_current_source (GDICT_SOURCE_CHOOSER (window->source_chooser),
                                             window->source_name);

  g_object_notify_by_pspec (G_OBJECT (window), gdict_window_properties[PROP_SOURCE_NAME]);
}
