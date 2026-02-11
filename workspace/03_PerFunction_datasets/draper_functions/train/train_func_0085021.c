get_writable_info (GFile *file)
{
  GFileAttributeInfoList *list;
  GError *error;
  int i;
  char *flags;

  if (file == NULL)
    return FALSE;

  error = NULL;

  list = g_file_query_settable_attributes (file, NULL, &error);
  if (list == NULL)
    {
      g_printerr (_("Error getting writable attributes: %s\n"), error->message);
      g_error_free (error);
      return FALSE;
    }

  g_print (_("Settable attributes:\n"));
  for (i = 0; i < list->n_infos; i++)
    {
      flags = attribute_flags_to_string (list->infos[i].flags);
      g_print (" %s (%s%s%s)\n",
	       list->infos[i].name,
	       attribute_type_to_string (list->infos[i].type),
	       (*flags != 0)?", ":"", flags);
      g_free (flags);
    }

  g_file_attribute_info_list_unref (list);

  list = g_file_query_writable_namespaces (file, NULL, &error);
  if (list == NULL)
    {
      g_printerr ("Error getting writable namespaces: %s\n", error->message);
      g_error_free (error);
      return FALSE;
    }

  if (list->n_infos > 0)
    {
      g_print (_("Writable attribute namespaces:\n"));
      for (i = 0; i < list->n_infos; i++)
	{
	  flags = attribute_flags_to_string (list->infos[i].flags);
	  g_print (" %s (%s%s%s)\n",
		   list->infos[i].name,
		   attribute_type_to_string (list->infos[i].type),
		   (*flags != 0)?", ":"", flags);
	}
    }

  g_file_attribute_info_list_unref (list);

  return TRUE;
}
