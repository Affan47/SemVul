tun_open(ifp)
struct interface *ifp;
{
	CK_IFNULL(ifp);
	CK_IFTYPE(ifp,IF_TYPE_TUN);

	if((ifp->status & IF_STAT_OPEN)) return 1;

	ifp->fd = open(ifp->devname, O_RDWR);
	if (ifp->fd<0) {
		PERR(ifp->devname);
		return -1;
	}

	if (fcntl(ifp->fd, F_SETFL, FNDELAY) < 0) {
		PERR("setting non-blocking I/O on tunnel device");
		return -1;
	}

	ifp->status = IF_STAT_OPEN;
	return 1;
}
