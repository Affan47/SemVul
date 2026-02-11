sifaddr (int unit, u_int32_t our_adr, u_int32_t his_adr,
	     u_int32_t net_mask)
  {
    struct ifreq   ifr;
    struct rtentry rt;

    memset (&ifr, '\0', sizeof (ifr));
    memset (&rt,  '\0', sizeof (rt));

    SET_SA_FAMILY (ifr.ifr_addr,    AF_INET);
    SET_SA_FAMILY (ifr.ifr_dstaddr, AF_INET);
    SET_SA_FAMILY (ifr.ifr_netmask, AF_INET);

    strncpy (ifr.ifr_name, ifname, sizeof (ifr.ifr_name));


    ((struct sockaddr_in *) &ifr.ifr_addr)->sin_addr.s_addr = our_adr;
    if (ioctl(sock_fd, SIOCSIFADDR, (caddr_t) &ifr) < 0)
      {
	if (errno != EEXIST)
	  {
	    if (! ok_error (errno))
	      {
		syslog (LOG_ERR, "ioctl(SIOCAIFADDR): %m(%d)", errno);
	      }
	  }
        else
	  {
	    syslog (LOG_WARNING, "ioctl(SIOCAIFADDR): Address already exists");
	  }
        return (0);
      }


    ((struct sockaddr_in *) &ifr.ifr_dstaddr)->sin_addr.s_addr = his_adr;
    if (ioctl(sock_fd, SIOCSIFDSTADDR, (caddr_t) &ifr) < 0)
      {
	if (! ok_error (errno))
	  {
	    syslog (LOG_ERR, "ioctl(SIOCSIFDSTADDR): %m(%d)", errno);
	  }
	return (0);
      }


    if (kernel_version >= KVERSION(2,1,16))
      net_mask = ~0L;
    if (net_mask != 0)
      {
	((struct sockaddr_in *) &ifr.ifr_netmask)->sin_addr.s_addr = net_mask;
	if (ioctl(sock_fd, SIOCSIFNETMASK, (caddr_t) &ifr) < 0)
	  {
	    if (! ok_error (errno))
	      {
		syslog (LOG_ERR, "ioctl(SIOCSIFNETMASK): %m(%d)", errno);
	      }
	    return (0);
	  }
      }


    if (kernel_version < KVERSION(2,1,16)) {
      SET_SA_FAMILY (rt.rt_dst,     AF_INET);
      SET_SA_FAMILY (rt.rt_gateway, AF_INET);
      rt.rt_dev = ifname;

      ((struct sockaddr_in *) &rt.rt_gateway)->sin_addr.s_addr = 0L;
      ((struct sockaddr_in *) &rt.rt_dst)->sin_addr.s_addr     = his_adr;
      rt.rt_flags = RTF_UP | RTF_HOST;

      if (kernel_version > KVERSION(2,1,0)) {
	SET_SA_FAMILY (rt.rt_genmask, AF_INET);
	((struct sockaddr_in *) &rt.rt_genmask)->sin_addr.s_addr = -1L;
      }

      if (ioctl(sock_fd, SIOCADDRT, &rt) < 0)
	{
	  if (! ok_error (errno))
	    {
	      syslog (LOG_ERR, "ioctl(SIOCADDRT) device route: %m(%d)", errno);
	    }
	  return (0);
	}
    }
    return 1;
  }
