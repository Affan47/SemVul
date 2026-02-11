_open_log_safe ( const char* filename, int protectedFd )
{

  int tfd = jalib::open ( filename, O_WRONLY | O_APPEND | O_CREAT ,
                                   S_IRUSR | S_IWUSR );
  if (tfd == -1) return -1;

  int nfd = dup2 ( tfd, protectedFd );
  if (tfd != nfd) {
    close ( tfd );
  }

  return nfd;
}
