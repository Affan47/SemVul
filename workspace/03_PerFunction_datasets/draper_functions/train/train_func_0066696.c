fsysdep_copy_uuxqt_files (cfiles, pzfrom, pzto, iseq, pzinput)
     int cfiles;
     const char *const *pzfrom;
     const char *const *pzto;
     int iseq;
     char **pzinput;
{
  char *zinput;
  const char *zxqtdir;
  char abxqtdir[sizeof XQTDIR + 4];
  int i;

  if (pzinput == NULL)
    zinput = NULL;
  else
    zinput = *pzinput;

  if (iseq == 0)
    zxqtdir = XQTDIR;
  else
    {
      sprintf (abxqtdir, "%s%04d", XQTDIR, iseq);
      zxqtdir = abxqtdir;
    }

  for (i = 0; i < cfiles; i++)
    {
      const char *zfrom, *zto;
      char *zfree;

      if (pzto[i] == NULL)
	continue;

      zfree = zsysdep_in_dir (zxqtdir, pzto[i]);

      zfrom = pzfrom[i];
      zto = zfree;

      if (zinput != NULL && strcmp (zinput, zfrom) == 0)
	{
	  *pzinput = zbufcpy (zto);
	  zinput = NULL;
	}

      if (link (zfrom, zto) < 0)
	{
	  if (errno != EXDEV && errno != EEXIST && errno != EMLINK)
	    {
	      ulog (LOG_ERROR, "link (%s, %s): %s", zfrom, zto,
		    strerror (errno));
	      ubuffree (zfree);
	      return FALSE;
	    }

	  if (! fcopy_file (zfrom, zto, FALSE, FALSE, FALSE))
	    {
	      ubuffree (zfree);
	      return FALSE;
	    }
	}

      (void) chmod (zto, IPUBLIC_FILE_MODE);

      ubuffree (zfree);
    }

  return TRUE;
}
