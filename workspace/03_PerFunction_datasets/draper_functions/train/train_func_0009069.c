get_proxy(mp, up)
MemPool mp;
URLParts *up;
{
  URLParts *pup = NULL;
  char *pname;
  char *apl;
# ifdef HAVE_UNAME
  struct utsname thishostname;
# endif

  if (up->scheme == NULL) return(NULL);


  pname = (char *)MPGet(mp, strlen(up->scheme) + strlen("_proxy") + 1);
  strcpy(pname, up->scheme);
  strcat(pname, "_proxy");
  if (getenv(pname) != NULL) pup = URLParse(mp, getenv(pname));


  if (pup == NULL)
  {


    if ((apl = getenv("all_proxy_list")) != NULL)
    {
      pname = apl;
      while ((pname = mystrtok(apl, ',', &apl)) != NULL)
      {
	if (strlen(up->scheme) == strlen(pname) &&
	    strcmp(up->scheme, pname) == 0) break;
      }
      if (pname == NULL) return(NULL);
    }
    if (getenv("all_proxy") != NULL) pup = URLParse(mp, getenv("all_proxy"));
  }


  if (pup == NULL) return(NULL);


# ifdef HAVE_UNAME
  uname(&thishostname);
  if (up->hostname &&


      ! match_no_proxy_list(up->hostname,
			    thishostname.nodename,
			    getenv("no_proxy"),
			    pup->hostname))
  {
    return(pup);
  }
# else
  if (up->hostname &&


      ! match_no_proxy_list(up->hostname,
			    NULL,
			    getenv("no_proxy"),
			    pup->hostname))
  {
    return(pup);
  }
# endif

  return(NULL);
}
