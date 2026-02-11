DB_ConnectInbox (DBConfig connect)
{
  struct stat status;

  if (connect.user[0] != '\0')
  {
    if ((stat (connect.user, &status)) != 0)
    {
      g_print (_("Cannot stat file %s!\n"), connect.user);
      return (1);
    }

    if (!((S_IFREG & status.st_mode) &&
        (((status.st_uid == geteuid ()) && (S_IXUSR & status.st_mode)) ||
         ((status.st_gid == getegid ()) && (S_IXGRP & status.st_mode)) ||
         (S_IXGRP & status.st_mode))))
    {
      g_print (_("File %s is not regular file or\nyou have not executable permission to this file!\n"),
               connect.user);
      return (2);
    }
  }

  action = connect.user;

  return (0);
}
