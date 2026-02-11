sipxfaddr (int unit, u_int32_t network, unsigned char * node )
  {
    int    skfd;
    int    result = 1;

    struct ifreq         ifr;
    struct sockaddr_ipx *sipx = (struct sockaddr_ipx *) &ifr.ifr_addr;

    skfd = socket (AF_IPX, SOCK_DGRAM, 0);
    if (skfd < 0)
      {
	syslog (LOG_DEBUG, "socket(AF_IPX): %m");
	result = 0;
      }
    else
      {
	memset (&ifr, '\0', sizeof (ifr));
	strcpy (ifr.ifr_name, lns[unit].ifname);

	memcpy (sipx->sipx_node, node, IPX_NODE_LEN);
	sipx->sipx_family  = AF_IPX;
	sipx->sipx_port    = 0;
	sipx->sipx_network = htonl (network);
	sipx->sipx_type    = IPX_FRAME_ETHERII;
	sipx->sipx_action  = IPX_CRTITF;


	if (ioctl(skfd, SIOCSIFADDR, (caddr_t) &ifr) < 0)
	  {
	    result = 0;
	    if (errno != EEXIST)
	      {
		syslog (LOG_DEBUG, "ioctl(SIOCAIFADDR, CRTITF): %m");
	      }
	    else
	      {
		syslog (LOG_WARNING,
			"ioctl(SIOCAIFADDR, CRTITF): Address already exists");
	      }
	  }
	close (skfd);
      }
    return result;
  }
