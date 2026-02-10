xchdir(int fd)
{
  if (((fd == 0) ? chdir("/") : fchdir(fd)) == -1)
    die1sys(1, "Could not change base directory");
}
