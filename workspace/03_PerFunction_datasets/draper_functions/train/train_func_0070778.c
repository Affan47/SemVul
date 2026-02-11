do_chown (int owner, int group, const char *path)
{
  int r;

  CHROOT_IN;
  r = chown (path, owner, group);
  CHROOT_OUT;

  if (r == -1) {
    reply_with_perror ("%s: %d.%d", path, owner, group);
    return -1;
  }

  return 0;
}
