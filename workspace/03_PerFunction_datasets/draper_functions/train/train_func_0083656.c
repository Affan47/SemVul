add_lecs(int itf, char *lecs)
{
	int fd;
	struct atmif_sioc req;
	struct sockaddr_atmsvc addr;

	memset(&addr, 0, sizeof(addr));
	addr.sas_family = AF_ATMSVC;
	memcpy(&addr.sas_addr.prv, lecs, 20);

	if ((fd = socket(AF_ATMSVC, SOCK_DGRAM, 0)) < 0){
		diag(COMPONENT, DIAG_ERROR, "socket: %s", strerror(errno));
		return;
	}

	req.number = itf;
	req.arg = &addr;
	req.length = sizeof(addr);

#ifdef ATM_ADDLECSADDR
	if (ioctl(fd, ATM_ADDLECSADDR, &req) < 0)
		diag(COMPONENT, DIAG_DEBUG, "ioctl ATM_ADDLECSADDR: %s", strerror(errno));
#else
	diag(COMPONENT, DIAG_DEBUG, "missing ATM_ADDLECSADDR support");
#endif

	close(fd);
	return;
}
