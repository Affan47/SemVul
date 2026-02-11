sifup (int u)
  {
    struct ifreq ifr;

    memset (&ifr, '\0', sizeof (ifr));
    strncpy(ifr.ifr_name, ifname, sizeof (ifr.ifr_name));
    if (ioctl(sock_fd, SIOCGIFFLAGS, (caddr_t) &ifr) < 0)
      {
	if (! ok_error (errno))
	  {
	    syslog(LOG_ERR, "ioctl (SIOCGIFFLAGS): %m(%d)", errno);
	  }
	return 0;
      }

    ifr.ifr_flags |= (IFF_UP | IFF_POINTOPOINT);
    if (ioctl(sock_fd, SIOCSIFFLAGS, (caddr_t) &ifr) < 0)
      {
	if (! ok_error (errno))
	  {
	    syslog(LOG_ERR, "ioctl(SIOCSIFFLAGS): %m(%d)", errno);
	  }
	return 0;
      }
    if_is_up = 1;
    return 1;
  }
