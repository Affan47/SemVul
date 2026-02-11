gconf_address_list_get_persistent_name (GSList *addresses)
{
  GSList  *tmp;
  GString *str = NULL;

  if (!addresses)
    {
      return g_strdup ("empty");
    }

  tmp = addresses;
  while (tmp != NULL)
    {
      const char *address = tmp->data;

      if (str == NULL)
	{
	  str = g_string_new (address);
	}
      else
        {
          g_string_append_c (str, GCONF_DATABASE_LIST_DELIM);
          g_string_append (str, address);
        }

      tmp = tmp->next;
    }

  return g_string_free (str, FALSE);
}
