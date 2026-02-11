cifaddr (int unit, u_int32_t our_adr, u_int32_t his_adr)
{
    struct ifreq ifr;

    if (kernel_version < KVERSION(2,1,16)) {


	struct rtentry rt;
	memset (&rt, '\0', sizeof (rt));

	SET_SA_FAMILY (rt.rt_dst,     AF_INET);
	SET_SA_FAMILY (rt.rt_gateway, AF_INET);
	rt.rt_dev = ifname;

	SIN_ADDR(rt.rt_gateway) = 0;
	SIN_ADDR(rt.rt_dst)     = his_adr;
	rt.rt_flags = RTF_UP | RTF_HOST;

	if (kernel_version > KVERSION(2,1,0)) {
	    SET_SA_FAMILY (rt.rt_genmask, AF_INET);
	    SIN_ADDR(rt.rt_genmask) = -1L;
	}

	if (ioctl(sock_fd, SIOCDELRT, &rt) < 0 && errno != ESRCH) {
	    if (still_ppp() && ! ok_error (errno))
		error("ioctl(SIOCDELRT) device route: %m (line %d)", __LINE__);
	    return (0);
	}
    }


    memset(&ifr, 0, sizeof(ifr));
    SET_SA_FAMILY(ifr.ifr_addr, AF_INET);
    strlcpy(ifr.ifr_name, ifname, sizeof(ifr.ifr_name));

    if (ioctl(sock_fd, SIOCSIFADDR, (caddr_t) &ifr) < 0) {
	if (! ok_error (errno)) {
	    error("ioctl(SIOCSIFADDR): %m (line %d)", __LINE__);
	    return 0;
	}
    }

    our_old_addr = our_adr;

    return 1;
}
