send_udp ()
{
  struct sockaddr_in dst;
  ssize_t err;

  memset (&dst, 0, sizeof (dst));
  dst.sin_family = AF_INET;
#if HAVE_SOCKADDR_IN_SIN_LEN
  dst.sin_len = sizeof (struct sockaddr_in);
#endif
  dst.sin_addr = dummy;
  dst.sin_port = htons (NAT_TRAV_PORT);
  err = sendto (udpsock, NULL, 0, 0, (struct sockaddr *) &dst, sizeof (dst));
  if (err < 0)
  {
#if VERBOSE
    fprintf (stderr, "sendto failed: %s\n", strerror (errno));
#endif
  }
  else if (0 != err)
  {
    fprintf (stderr, "Error: partial send of ICMP message\n");
  }
}
