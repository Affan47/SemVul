sifproxyarp (int unit, u_int32_t his_adr)
  {
    struct arpreq arpreq;

    if (has_proxy_arp == 0)
      {
	memset (&arpreq, '\0', sizeof(arpreq));

	SET_SA_FAMILY(arpreq.arp_pa, AF_INET);
	((struct sockaddr_in *) &arpreq.arp_pa)->sin_addr.s_addr = his_adr;
	arpreq.arp_flags = ATF_PERM | ATF_PUBL;


	if (!get_ether_addr(his_adr, &arpreq.arp_ha, arpreq.arp_dev))
	  {
	    syslog(LOG_ERR, "Cannot determine ethernet address for proxy ARP");
	    return 0;
	  }

	if (ioctl(sock_fd, SIOCSARP, (caddr_t)&arpreq) < 0)
	  {
	    if ( ! ok_error ( errno ))
	      {
		syslog(LOG_ERR, "ioctl(SIOCSARP): %m(%d)", errno);
	      }
	    return 0;
	  }
      }

    proxy_arp_addr = his_adr;
    has_proxy_arp = 1;
    return 1;
  }
