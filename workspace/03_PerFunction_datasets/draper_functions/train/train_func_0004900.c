fswork_file (zsystem, zfile, pbgrade)
     const char *zsystem ATTRIBUTE_UNUSED;
     const char *zfile;
     char *pbgrade;
{
#if SPOOLDIR_V2 || SPOOLDIR_BSD42 || SPOOLDIR_BSD43 || SPOOLDIR_ULTRIX
  int cfilesys, csys;


  if (zfile[0] != 'C' || zfile[1] != '.')
    return FALSE;
  csys = strlen (zsystem);
  cfilesys = strlen (zfile) - 7;
  if (csys != cfilesys
      && (csys < 6 || (cfilesys != 6 && cfilesys != 7)))
    return FALSE;
  *pbgrade = zfile[cfilesys + 2];
  return strncmp (zfile + 2, zsystem, cfilesys) == 0;
#endif
#if SPOOLDIR_HDB || SPOOLDIR_SVR4
  int clen;


  if (zfile[0] != 'C' || zfile[1] != '.')
    return FALSE;
  clen = strlen (zfile);
  if (clen < 7)
    return FALSE;
#if ! SPOOLDIR_SVR4
  *pbgrade = zfile[clen - 5];
#endif
  return TRUE;
#endif
#if SPOOLDIR_TAYLOR


  *pbgrade = zfile[2];
  return (zfile[0] == 'C'
	  && zfile[1] == '.'
	  && zfile[2] != '\0');
#endif
}
