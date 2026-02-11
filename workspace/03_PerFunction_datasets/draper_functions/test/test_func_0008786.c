sanei_ab306_close (int fd)
{
  Port *p = port + fd;

  if (p->in_use)
    {
      if (p->port_fd >= 0)
	{
	  close (p->port_fd);
	  p->port_fd = -1;
	}
      p->in_use = 0;
    }
}
