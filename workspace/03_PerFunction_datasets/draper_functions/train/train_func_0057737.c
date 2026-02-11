internal_getgrouplist (const char *user, gid_t group, long int *size,
		       gid_t **groupsp, long int limit)
{
#ifdef USE_NSCD
  if (__nss_not_use_nscd_group > 0
      && ++__nss_not_use_nscd_group > NSS_NSCD_RETRY)
    __nss_not_use_nscd_group = 0;
  if (!__nss_not_use_nscd_group
      && !__nss_database_custom[NSS_DBSIDX_group])
    {
      int n = __nscd_getgrouplist (user, group, size, groupsp, limit);
      if (n >= 0)
	return n;


      __nss_not_use_nscd_group = 1;
    }
#endif

  enum nss_status status = NSS_STATUS_UNAVAIL;
  int no_more = 0;


  assert (*size > 0);
  (*groupsp)[0] = group;

  long int start = 1;

  if (__nss_initgroups_database == NULL)
    {
      if (__nss_database_lookup ("initgroups", NULL, "",
				 &__nss_initgroups_database) < 0)
	{
	  if (__nss_group_database == NULL)
	    no_more = __nss_database_lookup ("group", NULL, "compat files",
					     &__nss_group_database);

	  __nss_initgroups_database = __nss_group_database;
	}
      else
	use_initgroups_entry = true;
    }
  else


    use_initgroups_entry = __nss_initgroups_database != __nss_group_database;

  service_user *nip = __nss_initgroups_database;
  while (! no_more)
    {
      long int prev_start = start;

      initgroups_dyn_function fct = __nss_lookup_function (nip,
							   "initgroups_dyn");
      if (fct == NULL)
	status = compat_call (nip, user, group, &start, size, groupsp,
			      limit, &errno);
      else
	status = DL_CALL_FCT (fct, (user, group, &start, size, groupsp,
				    limit, &errno));


      long int cnt = prev_start;
      while (cnt < start)
	{
	  long int inner;
	  for (inner = 0; inner < prev_start; ++inner)
	    if ((*groupsp)[inner] == (*groupsp)[cnt])
	      break;

	  if (inner < prev_start)
	    (*groupsp)[cnt] = (*groupsp)[--start];
	  else
	    ++cnt;
	}


      if (NSS_STATUS_TRYAGAIN > status || status > NSS_STATUS_RETURN)
	__libc_fatal ("illegal status in internal_getgrouplist");


      if ((use_initgroups_entry || status != NSS_STATUS_SUCCESS)
	  && nss_next_action (nip, status) == NSS_ACTION_RETURN)
	 break;

      if (nip->next == NULL)
	no_more = -1;
      else
	nip = nip->next;
    }

  return start;
}
