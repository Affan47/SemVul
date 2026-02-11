echo_dg (int s, struct servtab *sep _GL_UNUSED_PARAMETER)
{
  char buffer[BUFSIZE];
  int i;
  socklen_t size;
#ifdef IPV6
  struct sockaddr_storage sa;
#else
  struct sockaddr sa;
#endif

  size = sizeof sa;
  i = recvfrom (s, buffer, sizeof buffer, 0, (struct sockaddr *) &sa, &size);
  if (i < 0)
    return;
  sendto (s, buffer, i, 0, (struct sockaddr *) &sa, sizeof sa);
}
