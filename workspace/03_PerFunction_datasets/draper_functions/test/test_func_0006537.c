gconf_persistent_name_get_address_list (const char *persistent_name)
{
  char   delim [2] = { GCONF_DATABASE_LIST_DELIM, '\0' };
  char **address_vector;

  address_vector = g_strsplit (persistent_name, delim, -1);
  if (address_vector != NULL)
    {
      GSList  *retval = NULL;
      int      i;

      i = 0;
      while (address_vector [i] != NULL)
        {
          retval = g_slist_append (retval, g_strdup (address_vector [i]));
          ++i;
        }

      g_strfreev (address_vector);

      return retval;
    }
  else
    {
      return g_slist_append (NULL, g_strdup (persistent_name));
    }
}
