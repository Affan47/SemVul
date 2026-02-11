entry_fill_from_node(Entry* e)
{
  gchar* tmp;
  GError* error = NULL;

  g_return_if_fail(e->node != NULL);

  tmp = my_xmlGetProp(e->node, "schema");

  if (tmp != NULL)
    {

      gchar* why_bad = NULL;
      if (gconf_valid_key(tmp, &why_bad))
        {
          g_assert(why_bad == NULL);
          e->schema_name = g_strdup(tmp);
        }
      else
        {
          e->schema_name = NULL;
          gconf_log(GCL_WARNING, _("Ignoring schema name `%s', invalid: %s"),
                    tmp, why_bad);
          g_free(why_bad);
        }

      xmlFree(tmp);
    }

  tmp = my_xmlGetProp(e->node, "mtime");

  if (tmp != NULL)
    {
      e->mod_time = gconf_string_to_gulong(tmp);
      xmlFree(tmp);
    }
  else
    e->mod_time = 0;

  tmp = my_xmlGetProp(e->node, "muser");

  if (tmp != NULL)
    {
      e->mod_user = g_strdup(tmp);
      xmlFree(tmp);
    }
  else
    e->mod_user = NULL;

  entry_sync_if_needed(e);

  if (e->cached_value != NULL)
    gconf_value_free(e->cached_value);

  e->cached_value = node_extract_value(e->node, NULL,
                                       &error);

  if (e->cached_value)
    {
      g_return_if_fail(error == NULL);
      return;
    }
  else if (error != NULL)
    {


      if (e->schema_name == NULL)
        gconf_log (GCL_WARNING,
                   _("Ignoring XML node `%s': %s"),
                   e->name, error->message);
      g_error_free(error);
    }
}
