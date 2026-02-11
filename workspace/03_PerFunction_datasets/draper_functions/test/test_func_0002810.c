verify_pid(int pid)
{
  int res;

  res = kill(pid, 0);
  if (res < 0 && errno == EPERM) {
    fprintf(stderr, "Not process owner\n");
    exit(1);
  }

  return(res == 0);
}
