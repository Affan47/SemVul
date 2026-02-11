LockPostRec(char *path)
{
  char lockname[SPOOLNAMEBUFF];
  char temp[SPOOLNAMEBUFF];
  int statfailed = 0;

  snprintf(lockname, sizeof(lockname), "%s.lock", path);

  for (;; sleep(5)) {
    int fd;
    struct stat st;
    time_t now;

    fd = open(lockname, O_WRONLY|O_EXCL|O_CREAT, 0600);
    if (fd >= 0) {

      snprintf(temp, sizeof(temp), "pid:%ld\n", (unsigned long) getpid());
      write(fd, temp, strlen(temp));
      close(fd);
      return(1);
    }


    if (stat(lockname, &st) < 0) {
      syslog(L_ERROR, "%s cannot stat lock file %s", Client.host, strerror(errno));
      if (statfailed++ > 5)
          return(0);
      continue;
    }


    statfailed = 0;
    time(&now);
    if (now < (time_t) (st.st_ctime + PERMaccessconf->backoff_postslow))
        continue;
    syslog(L_ERROR, "%s removing stale lock file %s", Client.host, lockname);
    unlink(lockname);
  }
}
