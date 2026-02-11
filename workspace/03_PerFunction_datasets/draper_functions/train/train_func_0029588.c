socket_get_farside_pid(int sockfd)
{
  socklen_t n;
  struct ucred *cred;
  pid_t f_pid;


  n = sizeof(struct ucred);
  cred = g_new(struct ucred, 1);
  if (getsockopt(sockfd, SOL_SOCKET, SO_PEERCRED, cred, &n) != 0) {
    g_free(cred);
    return -1;
  }

  f_pid = cred->pid;
  g_free(cred);
  return f_pid;
}
