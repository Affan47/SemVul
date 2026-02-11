translate_unix_perms (enum GNUNET_DISK_AccessPermissions perm)
{
  int mode;

  mode = 0;
  if (perm & GNUNET_DISK_PERM_USER_READ)
    mode |= S_IRUSR;
  if (perm & GNUNET_DISK_PERM_USER_WRITE)
    mode |= S_IWUSR;
  if (perm & GNUNET_DISK_PERM_USER_EXEC)
    mode |= S_IXUSR;
  if (perm & GNUNET_DISK_PERM_GROUP_READ)
    mode |= S_IRGRP;
  if (perm & GNUNET_DISK_PERM_GROUP_WRITE)
    mode |= S_IWGRP;
  if (perm & GNUNET_DISK_PERM_GROUP_EXEC)
    mode |= S_IXGRP;
  if (perm & GNUNET_DISK_PERM_OTHER_READ)
    mode |= S_IROTH;
  if (perm & GNUNET_DISK_PERM_OTHER_WRITE)
    mode |= S_IWOTH;
  if (perm & GNUNET_DISK_PERM_OTHER_EXEC)
    mode |= S_IXOTH;

  return mode;
}
