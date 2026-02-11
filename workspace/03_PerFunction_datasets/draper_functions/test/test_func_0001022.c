sifup (int u)
{
	struct ifreq ifr;
	u_int x;

	memset (&ifr, '\0', sizeof (ifr));
	strncpy(ifr.ifr_name, lns[u].ifname, sizeof (ifr.ifr_name));
	if (ioctl(sockfd, SIOCGIFFLAGS, (caddr_t) &ifr) < 0) {
		syslog(LOG_ERR, "Ifup: ioctl (SIOCGIFFLAGS): %m");
		return 0;
	}

	ifr.ifr_flags |= (IFF_UP | IFF_POINTOPOINT);
    if (ioctl(sockfd, SIOCSIFFLAGS, (caddr_t) &ifr) < 0) {
		syslog(LOG_ERR, "Ifup: ioctl(SIOCSIFFLAGS): %m");
		return 0;
	}
    if( ioctl(lns[u].fd,PPPIOCGFLAGS,(caddr_t) &x) < 0) {
		syslog(LOG_ERR,"Ifup: ioctl(PPPIOCGFLAGS) on %d: %m",lns[u].fd);
		return 0;
	}
	x |= SC_ENABLE_IP;
	if( ioctl(lns[u].fd,PPPIOCSFLAGS,(caddr_t) &x) < 0) {
		syslog(LOG_ERR,"Ifup: ioctl(PPPIOCSFLAGS): %m");
		return 0;
	}
	return 1;
}
