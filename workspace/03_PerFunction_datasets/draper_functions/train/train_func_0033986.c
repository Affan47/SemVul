read_n_bytes (int fd, char *buffer, int n)
{
  int totalcnt;
  int cnt;

  totalcnt = 0;
  while (totalcnt < n) {
    cnt = read (fd, buffer + totalcnt, n);
    if (cnt == -1)
      return FALSE;
    totalcnt += cnt;
  }

  return TRUE;
}
