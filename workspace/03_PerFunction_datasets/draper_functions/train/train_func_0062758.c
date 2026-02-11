fsysdep_get_xqt_init (zsystem)
     const char *zsystem;
{
  usysdep_get_xqt_free ((const char *) NULL);

#if SUBDIRS
  if (zsystem != NULL)
    {
#if SPOOLDIR_HDB || SPOOLDIR_SVR4
      zSdir = zbufcpy (zsystem);
#endif
#if SPOOLDIR_ULTRIX
      zSdir = zsappend3 ("sys", zsystem, "X.");
#endif
#if SPOOLDIR_TAYLOR
      zSdir = zsysdep_in_dir (zsystem, "X.");
#endif

      qSxqt_dir = opendir ((char *) zSdir);
      if (qSxqt_dir != NULL)
	{
	  qSxqt_topdir = qSxqt_dir;
	  fSone_dir = TRUE;
	  zSsystem = zbufcpy (zsystem);
	  return TRUE;
	}
    }

  fSone_dir = FALSE;
#endif

  qSxqt_topdir = opendir ((char *) ZDIR);
  if (qSxqt_topdir == NULL)
    {
      if (errno == ENOENT)
	return TRUE;
      ulog (LOG_ERROR, "opendir (%s): %s", ZDIR, strerror (errno));
      return FALSE;
    }

  return TRUE;
}
