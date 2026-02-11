dump_entries_in_dir(GConfEngine* conf, const gchar* dir, const gchar* base_dir)
{
  GSList* entries;
  GSList* tmp;
  GError* err = NULL;

  entries = g_slist_sort(gconf_engine_all_entries(conf, dir, &err),
			 (GCompareFunc)compare_entries);

  if (err != NULL)
    {
      g_printerr (_("Failure listing entries in `%s': %s\n"),
		  dir, err->message);
      g_error_free(err);
      err = NULL;
    }

  tmp = entries;
  while (tmp != NULL)
    {
      GConfEntry* entry = tmp->data;

      g_print ("    <entry>\n");

      g_print ("      <key>%s</key>\n",
	       get_key_relative(gconf_entry_get_key(entry), base_dir));


      if (gconf_entry_get_schema_name(entry))
        g_print ("      <schema_key>%s</schema_key>\n",
		 get_key_relative(gconf_entry_get_schema_name(entry), base_dir));

      if (entry->value &&
	  (!ignore_schema_defaults || !gconf_entry_get_is_default(entry)))
        print_value_in_xml(entry->value, 6);

      g_print ("    </entry>\n");

      gconf_entry_free(entry);

      tmp = tmp->next;
    }
  g_slist_free(entries);
}
