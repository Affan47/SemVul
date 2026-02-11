get_context_from_loader (GtrDictPanel * panel)
{
  GtrDictPanelPrivate *priv = panel->priv;
  GdictSource *source;
  GdictContext *retval;

  if (!priv->source_name)
    priv->source_name = g_strdup (DICTIONARY_DEFAULT_SOURCE_NAME);

  source = gdict_source_loader_get_source (priv->loader, priv->source_name);
  if (!source)
    {
      gchar *detail;

      detail =
        g_strdup_printf (_("No dictionary source available with name '%s'"),
                         priv->source_name);

      gtr_dict_panel_create_warning_dialog (_
                                            ("Unable to find dictionary source"),
                                            detail);
      g_free (detail);

      return NULL;
    }

  gtr_dict_panel_set_database (panel, gdict_source_get_database (source));
  gtr_dict_panel_set_strategy (panel, gdict_source_get_strategy (source));

  retval = gdict_source_get_context (source);
  if (!retval)
    {
      gchar *detail;

      detail = g_strdup_printf (_("No context available for source '%s'"),
                                gdict_source_get_description (source));

      gtr_dict_panel_create_warning_dialog (_
                                            ("Unable to create a context"),
                                            detail);

      g_free (detail);
      g_object_unref (source);

      return NULL;
    }

  g_object_unref (source);

  return retval;
}
