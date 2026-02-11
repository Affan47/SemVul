openInterface(char const *ifname, UINT16_t type, unsigned char *hwaddr)
{
    int optval=1;
    int fd;
    struct ifreq ifr;
    int domain, stype;

#ifdef HAVE_STRUCT_SOCKADDR_LL
    struct sockaddr_ll sa;
#else
    struct sockaddr sa;
#endif

    memset(&sa, 0, sizeof(sa));

#ifdef HAVE_STRUCT_SOCKADDR_LL
    domain = PF_PACKET;
    stype = SOCK_RAW;
#else
    domain = PF_INET;
    stype = SOCK_PACKET;
#endif

    if ((fd = socket(domain, stype, htons(type))) < 0) {

	if (errno == EPERM) {
	    fatal("Cannot create raw socket -- pppoe must be run as root.");
	}
	fatal("cannot create the raw socket: %m");
    }

    if (setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &optval, sizeof(optval)) < 0) {
	fatal("setsockopt(SOL_SOCKET, SO_BROADCAST): %m");
    }


    if (hwaddr) {
	strncpy(ifr.ifr_name, ifname, sizeof(ifr.ifr_name));
	if (ioctl(fd, SIOCGIFHWADDR, &ifr) < 0)
	    fatal("ioctl(SIOCGIFHWADDR): %m");
	memcpy(hwaddr, ifr.ifr_hwaddr.sa_data, ETH_ALEN);
#ifdef ARPHRD_ETHER
	if (ifr.ifr_hwaddr.sa_family != ARPHRD_ETHER) {
	    fatal("Interface %s is not Ethernet", ifname);
	}
#endif
	if (NOT_UNICAST(hwaddr)) {
	    fatal("Interface %s has broadcast/multicast MAC address",
		    ifname);
	}
    }


    strncpy(ifr.ifr_name, ifname, sizeof(ifr.ifr_name));
    if (ioctl(fd, SIOCGIFMTU, &ifr) < 0) {
	fatal("ioctl(SIOCGIFMTU): %m");
    }
    if (ifr.ifr_mtu < ETH_DATA_LEN) {
	error("Interface %s has MTU of %d -- should be %d."
		"  You may have serious connection problems.",
		ifname, ifr.ifr_mtu, ETH_DATA_LEN);
    }

#ifdef HAVE_STRUCT_SOCKADDR_LL

    sa.sll_family = AF_PACKET;
    sa.sll_protocol = htons(type);

    strncpy(ifr.ifr_name, ifname, sizeof(ifr.ifr_name));
    if (ioctl(fd, SIOCGIFINDEX, &ifr) < 0) {
	fatal("ioctl(SIOCFIGINDEX): Could not get interface index: %m");
    }
    sa.sll_ifindex = ifr.ifr_ifindex;

#else
    strcpy(sa.sa_data, ifname);
#endif


    if (bind(fd, (struct sockaddr *) &sa, sizeof(sa)) < 0) {
	fatal("bind: %m");
    }

    return fd;
}
