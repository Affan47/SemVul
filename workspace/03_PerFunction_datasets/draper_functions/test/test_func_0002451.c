ReadLock(int fd)
{
  int i;
  pid_t pid;
  char buff[BUFSIZ];

  lseek(fd, 0, SEEK_SET);


  if (BinaryLock) {
    if (read(fd, (char *)&pid, sizeof(pid)) != sizeof(pid)) {
      return 0;
    }
  } else {
    if ((i = read(fd, buff, sizeof(buff) - 1)) <= 0) {
      return 0;
    }
    buff[i] = '\0';
    pid = (pid_t) atol(buff);
  }
  return pid;
}
