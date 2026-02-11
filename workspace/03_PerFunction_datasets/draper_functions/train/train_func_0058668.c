socket_connect (const socket_st * hd)
{
  int err;

  printf ("Connecting to '%s:%s'...\n", hd->ip, hd->service);

  err = connect (hd->fd, hd->ptr->ai_addr, hd->ptr->ai_addrlen);
  if (err < 0)
    {
      fprintf (stderr, "Cannot connect to %s:%s: %s\n", hd->hostname,
               hd->service, strerror (errno));
      exit (1);
    }
}
