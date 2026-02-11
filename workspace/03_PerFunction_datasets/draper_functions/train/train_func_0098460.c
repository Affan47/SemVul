ixsysdep_user_file_mode (zfile)
     const char *zfile;
{
  uid_t ieuid;
  gid_t iegid;
  int iret;
  struct stat s;

  if (! fsuser_perms (&ieuid, &iegid))
    return 0;

  iret = stat ((char *) zfile, &s);

  if (! fsuucp_perms ((long) ieuid, (long) iegid))
    return 0;

  if (iret != 0)
    {
      ulog (LOG_ERROR, "stat (%s): %s", zfile, strerror (errno));
      return 0;
    }


  if ((s.st_mode & 0777) == 0)
    return 0400;

  return s.st_mode & 0777;
}
