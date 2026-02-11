Ifconfig_Set_IP(const char *in_dev, char *errstr, const char *ip) {
	struct ifreq ifr;
	int skfd;
	struct sockaddr_in sin;
	struct hostent *hp;

	sin.sin_family = AF_INET;
	sin.sin_port = 0;

	if ((hp = gethostbyname(ip)) != NULL) {
		memcpy(&(sin.sin_addr), hp->h_addr_list[0], sizeof(struct in_addr));
	} else {
		snprintf(errstr, STATUS_MAX, "Setting IPAddr: unable to resolve address %s",
				 ip);
		return -1;
	}

    if ((skfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        snprintf(errstr, STATUS_MAX, "Setting IPAddr: failed to create AF_INET "
                 "DGRAM socket. %s", strerror(errno));
        return -1;
    }

    strncpy(ifr.ifr_name, in_dev, IFNAMSIZ);

	memcpy(&(ifr.ifr_addr), &sin, sizeof(struct sockaddr));

	if (ioctl(skfd, SIOCSIFADDR, &ifr) < 0) {
        snprintf(errstr, STATUS_MAX, "Setting IPAddr failed %s: %s",
                 in_dev, strerror(errno));
        close(skfd);
        return -1;
    }

    close(skfd);

	return 0;
}
