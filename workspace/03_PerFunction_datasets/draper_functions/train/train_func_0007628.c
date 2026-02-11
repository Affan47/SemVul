visu_config_file_exportToXML(const gchar *filename, int kind, GError **error)
{
  GString *str;
  GList *tmpLst;
  VisuConfigFileEntry *entry;
  gboolean status;
  gchar *desc;

  g_return_val_if_fail(filename && *filename, FALSE);
  g_return_val_if_fail(kind == VISU_CONFIG_FILE_RESOURCE ||
		       kind == VISU_CONFIG_FILE_PARAMETER, FALSE);

  str = g_string_new("<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
  if (kind == VISU_CONFIG_FILE_PARAMETER)
    {
      tmpLst = registeredParameters;
      g_string_append_printf(str, "<configFile kind=\"parameters\">\n");
    }
  else
    {
      tmpLst = registeredResources;
      g_string_append_printf(str, "<configFile kind=\"resources\">\n");
    }
  while (tmpLst)
    {
      entry = (VisuConfigFileEntry*)tmpLst->data;
      if (entry->tag)
	g_string_append_printf(str, "  <entry name=\"%s\" tag=\"%s\" "
			       "version=\"%f3.1\">\n",
			       entry->key, entry->tag, entry->version);
      else
	g_string_append_printf(str, "  <entry name=\"%s\" version=\"%3.1f\">\n",
			       entry->key, entry->version);
      desc = g_markup_escape_text(entry->description, -1);
      g_string_append_printf(str, "    <description>%s</description>\n", desc);
      g_free(desc);
      if (entry->newKey)
	g_string_append_printf(str, "    <obsolete replacedBy=\"%s\" />\n",
			       entry->newKey);
      g_string_append_printf(str, "  </entry>\n");
      tmpLst = g_list_next(tmpLst);
    }
  g_string_append_printf(str, "</configFile>\n");

  status = g_file_set_contents(filename, str->str, -1, error);
  g_string_free(str, TRUE);
  return status;
}
