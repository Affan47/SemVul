fctranslate (puuconf, zphone, pzprefix, pzsuffix)
     pointer puuconf;
     const char *zphone;
     const char **pzprefix;
     const char **pzsuffix;
{
  int iuuconf;
  char *zdialcode, *zto;
  const char *zfrom;
  char *ztrans;

  *pzprefix = zphone;
  *pzsuffix = NULL;

  zdialcode = zbufalc (strlen (zphone) + 1);
  zfrom = zphone;
  zto = zdialcode;
  while (*zfrom != '\0' && isalpha (BUCHAR (*zfrom)))
    *zto++ = *zfrom++;
  *zto = '\0';

  if (*zdialcode == '\0')
    {
      ubuffree (zdialcode);
      return TRUE;
    }

  iuuconf = uuconf_dialcode (puuconf, zdialcode, &ztrans);

  ubuffree (zdialcode);

  if (iuuconf == UUCONF_NOT_FOUND)
    return TRUE;
  else if (iuuconf != UUCONF_SUCCESS)
    {
      ulog_uuconf (LOG_ERROR, puuconf, iuuconf);
      return FALSE;
    }
  else
    {

      *pzprefix = ztrans;
      *pzsuffix = zfrom;
      return TRUE;
    }
}
