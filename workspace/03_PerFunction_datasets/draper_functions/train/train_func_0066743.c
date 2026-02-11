internal_gid_from_group (void *context, const char *groupname, gid_t *group)
{
  char **grp_res;
  enum nss_status status = NSS_STATUS_NOTFOUND;

  grp_res = hesiod_resolve (context, groupname, "group");
  if (grp_res != NULL && *grp_res != NULL)
    {
      char *p = *grp_res;


      while (*p != '\0' && *p != ':')
	++p;
      if (*p != '\0')
	++p;
      while (*p != '\0' && *p != ':')
	++p;
      if (*p != '\0')
	{
	  char *endp;
	  char *q = ++p;
	  long int val;

	  while (*q != '\0' && *q != ':')
	    ++q;

	  val = strtol (p, &endp, 10);
	  if (sizeof (gid_t) == sizeof (long int) || (gid_t) val == val)
	    {
	      *group = val;
	      if (endp == q && endp != p)
		status = NSS_STATUS_SUCCESS;
	    }
        }
      hesiod_free_list (context, grp_res);
    }
  return status;
}
