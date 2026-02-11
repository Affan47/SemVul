gconf_address_backend(const gchar* address)
{
  const gchar* end;

  g_return_val_if_fail(address != NULL, NULL);

  end = strchr(address, ':');

  if (end == NULL)
    {
      return NULL;
    }
  else
    {
      int len = end-address+1;
      gchar* retval = g_malloc(len);
      strncpy(retval, address, len-1);
      retval[len-1] = '\0';
      return retval;
    }
}
