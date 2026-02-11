machtime_dg (int s, struct servtab *sep _GL_UNUSED_PARAMETER)
{
  long result;
#ifdef IPV6
  struct sockaddr_storage sa;
#else
  struct sockaddr sa;
#endif
  socklen_t size;

  size = sizeof sa;
  if (recvfrom (s, (char *) &result, sizeof result, 0,
		(struct sockaddr *) &sa, &size) < 0)
    return;
  result = machtime ();
  sendto (s, (char *) &result, sizeof result, 0,
	  (struct sockaddr *) &sa, sizeof sa);
}
