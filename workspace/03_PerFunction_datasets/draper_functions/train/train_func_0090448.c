get_context_from_loader (GdictWindow *window)
{
  GdictSource *source;
  GdictContext *retval;

  if (!window->source_name)
    window->source_name = g_strdup (GDICT_DEFAULT_SOURCE_NAME);

  source = gdict_source_loader_get_source (window->loader,
		  			   window->source_name);
  if (!source &&
      strcmp (window->source_name, GDICT_DEFAULT_SOURCE_NAME) != 0)
    {
      g_free (window->source_name);
      window->source_name = g_strdup (GDICT_DEFAULT_SOURCE_NAME);

      source = gdict_source_loader_get_source (window->loader,
                                               window->source_name);
    }

  if (!source)
    {
      gchar *detail;

      detail = g_strdup_printf (_("No dictionary source available with name '%s'"),
      				window->source_name);

      gdict_show_error_dialog (GTK_WINDOW (window),
                               _("Unable to find dictionary source"),
                               detail);

      g_free (detail);

      return NULL;
    }

  gdict_window_set_database (window, gdict_source_get_database (source));
  gdict_window_set_strategy (window, gdict_source_get_strategy (source));

  retval = gdict_source_get_context (source);
  if (!retval)
    {
      gchar *detail;

      detail = g_strdup_printf (_("No context available for source '%s'"),
      				gdict_source_get_description (source));

      gdict_show_error_dialog (GTK_WINDOW (window),
                               _("Unable to create a context"),
                               detail);

      g_free (detail);
      g_object_unref (source);

      return NULL;
    }

  g_object_unref (source);

  return retval;
}
