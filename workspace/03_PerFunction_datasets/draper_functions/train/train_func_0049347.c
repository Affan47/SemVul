__nss_database_lookup (const char *database, const char *alternate_name,
		       const char *defconfig, service_user **ni)
{

  lock_nsswitch;


  if (*ni != NULL)
    {
      unlock_nsswitch;
      return 0;
    }

#if __OPTION_EGLIBC_NSSWITCH

  if (service_table == NULL)

    service_table = nss_parse_file (_PATH_NSSWITCH_CONF);
#endif


  if (service_table != NULL)
    {

      name_database_entry *entry;


      for (entry = service_table->entry; entry != NULL; entry = entry->next)
	if (strcmp (database, entry->name) == 0)
	  *ni = entry->service;

      if (*ni == NULL && alternate_name != NULL)


	for (entry = service_table->entry; entry != NULL; entry = entry->next)
	  if (strcmp (alternate_name, entry->name) == 0)
	    *ni = entry->service;
    }

#if __OPTION_EGLIBC_NSSWITCH


  if (*ni == NULL)
    {
      *ni = nss_parse_service_list (defconfig
				    ?: "nis [NOTFOUND=return] files");
      if (*ni != NULL)
	{


	  name_database_entry *entry;


	  entry = (name_database_entry *) malloc (sizeof (*entry) + 1);

	  if (entry != NULL)
	    {
	      entry->next = defconfig_entries;
	      entry->service = *ni;
	      entry->name = "";
	      defconfig_entries = entry;
	    }
	}
    }
#else


  if (*ni == NULL)
    {
      unlock_nsswitch;
      return -1;
    }
#endif

  unlock_nsswitch;

  return *ni != NULL ? 0 : -1;
}
