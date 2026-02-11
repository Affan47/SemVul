zsysdep_all_status (phold, pferr, qstat)
     pointer phold;
     boolean *pferr;
     struct sstatus *qstat;
{
  DIR *qdir = (DIR *) phold;
  struct dirent *qentry;

  while (TRUE)
    {
      errno = 0;
      qentry = readdir (qdir);
      if (qentry == NULL)
	{
	  if (errno == 0)
	    *pferr = FALSE;
	  else
	    {
	      ulog (LOG_ERROR, "readdir: %s", strerror (errno));
	      *pferr = TRUE;
	    }
	  return NULL;
	}

      if (qentry->d_name[0] != '.')
	{
	  struct uuconf_system ssys;


	  ssys.uuconf_zname = qentry->d_name;
	  if (fsysdep_get_status (&ssys, qstat, (boolean *) NULL))
	    return zbufcpy (qentry->d_name);


	}
    }
}
