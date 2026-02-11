uuconf_taylor_callout (pglobal, qsys, pzlog, pzpass)
     pointer pglobal;
     const struct uuconf_system *qsys;
     char **pzlog;
     char **pzpass;
{
  struct sglobal *qglobal = (struct sglobal *) pglobal;
  boolean flookup;
  struct uuconf_cmdtab as[2];
  char **pz;
  int iret;
  pointer pinfo;

  *pzlog = NULL;
  *pzpass = NULL;

  flookup = FALSE;

  if (qsys->uuconf_zcall_login != NULL)
    {
      if (strcmp (qsys->uuconf_zcall_login, "*") == 0)
	flookup = TRUE;
      else
	{
	  *pzlog = strdup (qsys->uuconf_zcall_login);
	  if (*pzlog == NULL)
	    {
	      qglobal->ierrno = errno;
	      return UUCONF_MALLOC_FAILED | UUCONF_ERROR_ERRNO;
	    }
	}
    }

  if (qsys->uuconf_zcall_password != NULL)
    {
      if (strcmp (qsys->uuconf_zcall_password, "*") == 0)
	flookup = TRUE;
      else
	{
	  *pzpass = strdup (qsys->uuconf_zcall_password);
	  if (*pzpass == NULL)
	    {
	      qglobal->ierrno = errno;
	      if (*pzlog != NULL)
		{
		  free ((pointer) *pzlog);
		  *pzlog = NULL;
		}
	      return UUCONF_MALLOC_FAILED | UUCONF_ERROR_ERRNO;
	    }
	}
    }

  if (! flookup)
    {
      if (*pzlog == NULL && *pzpass == NULL)
	return UUCONF_NOT_FOUND;
      return UUCONF_SUCCESS;
    }

  as[0].uuconf_zcmd = qsys->uuconf_zname;
  as[0].uuconf_itype = UUCONF_CMDTABTYPE_FN | 0;
  if (*pzlog == NULL)
    as[0].uuconf_pvar = (pointer) pzlog;
  else
    as[0].uuconf_pvar = NULL;
  as[0].uuconf_pifn = icsys;

  as[1].uuconf_zcmd = NULL;

  if (*pzpass == NULL)
    pinfo = (pointer) pzpass;
  else
    pinfo = NULL;

  iret = UUCONF_SUCCESS;

  for (pz = qglobal->qprocess->pzcallfiles; *pz != NULL; pz++)
    {
      FILE *e;

      e = fopen (*pz, "r");
      if (e == NULL)
	{
	  if (FNO_SUCH_FILE ())
	    continue;
	  qglobal->ierrno = errno;
	  iret = UUCONF_FOPEN_FAILED | UUCONF_ERROR_ERRNO;
	  break;
	}

      iret = uuconf_cmd_file (pglobal, e, as, pinfo,
			      (uuconf_cmdtabfn) NULL, 0,
			      qsys->uuconf_palloc);
      (void) fclose (e);

      if (iret != UUCONF_SUCCESS)
	break;
      if (*pzlog != NULL)
	break;
    }

  if (iret != UUCONF_SUCCESS)
    {
      qglobal->zfilename = *pz;
      return iret | UUCONF_ERROR_FILENAME;
    }

  if (*pzlog == NULL && *pzpass == NULL)
    return UUCONF_NOT_FOUND;

  return UUCONF_SUCCESS;
}
