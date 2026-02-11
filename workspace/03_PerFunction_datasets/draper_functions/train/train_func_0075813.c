unlock_common(const char * filename, int fd)
{
  char lockfilename[PATH_MAX];
  struct flock lock;
  int r;

  if (strlen(filename) + 6 > PATH_MAX)
    return -1;

  snprintf(lockfilename, PATH_MAX, "%s.lock", filename);

  unlink(lockfilename);

  lock.l_start = 0;
  lock.l_len = 0;
  lock.l_pid = getpid();
  lock.l_type = F_UNLCK;
  lock.l_whence = SEEK_SET;

  r = fcntl(fd, F_SETLK, &lock);
  if (r < 0) {

  }

  return 0;
}
