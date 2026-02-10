GNUNET_DISK_directory_scan (const char *dirName,
                            GNUNET_FileNameCallback callback,
                            void *callback_cls)
{
  DIR *dinfo;
  struct dirent *finfo;
  struct stat istat;
  int count = 0;
  char *name;
  char *dname;
  unsigned int name_len;
  unsigned int n_size;

  GNUNET_assert (dirName != NULL);
  dname = GNUNET_STRINGS_filename_expand (dirName);
  if (dname == NULL)
    return GNUNET_SYSERR;
  while ((strlen (dname) > 0) && (dname[strlen (dname) - 1] == DIR_SEPARATOR))
    dname[strlen (dname) - 1] = '\0';
  if (0 != STAT (dname, &istat))
  {
    LOG_STRERROR_FILE (GNUNET_ERROR_TYPE_WARNING, "stat", dname);
    GNUNET_free (dname);
    return GNUNET_SYSERR;
  }
  if (!S_ISDIR (istat.st_mode))
  {
    LOG (GNUNET_ERROR_TYPE_WARNING, _("Expected `%s' to be a directory!\n"),
         dirName);
    GNUNET_free (dname);
    return GNUNET_SYSERR;
  }
  errno = 0;
  dinfo = OPENDIR (dname);
  if ((errno == EACCES) || (dinfo == NULL))
  {
    LOG_STRERROR_FILE (GNUNET_ERROR_TYPE_WARNING, "opendir", dname);
    if (dinfo != NULL)
      CLOSEDIR (dinfo);
    GNUNET_free (dname);
    return GNUNET_SYSERR;
  }
  name_len = 256;
  n_size = strlen (dname) + name_len + 2;
  name = GNUNET_malloc (n_size);
  while ((finfo = READDIR (dinfo)) != NULL)
  {
    if ((0 == strcmp (finfo->d_name, ".")) ||
        (0 == strcmp (finfo->d_name, "..")))
      continue;
    if (callback != NULL)
    {
      if (name_len < strlen (finfo->d_name))
      {
        GNUNET_free (name);
        name_len = strlen (finfo->d_name);
        n_size = strlen (dname) + name_len + 2;
        name = GNUNET_malloc (n_size);
      }


      GNUNET_snprintf (name, n_size, "%s%s%s", dname,
                       (strcmp (dname, DIR_SEPARATOR_STR) ==
                        0) ? "" : DIR_SEPARATOR_STR, finfo->d_name);
      if (GNUNET_OK != callback (callback_cls, name))
      {
        CLOSEDIR (dinfo);
        GNUNET_free (name);
        GNUNET_free (dname);
        return GNUNET_SYSERR;
      }
    }
    count++;
  }
  CLOSEDIR (dinfo);
  GNUNET_free (name);
  GNUNET_free (dname);
  return count;
}
