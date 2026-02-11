asroot_iface_init()
{
	int rc = -1, fd = -1;
	int ifindex;
	char name[IFNAMSIZ];
	must_read(PRIV_PRIVILEGED, &ifindex, sizeof(ifindex));
	must_read(PRIV_PRIVILEGED, &name, sizeof(name));
	name[sizeof(name) - 1] = '\0';

	TRACE(LLDPD_PRIV_INTERFACE_INIT(name));
	rc = asroot_iface_init_os(ifindex, name, &fd);
	must_write(PRIV_PRIVILEGED, &rc, sizeof(rc));
	if (rc == 0 && fd >=0) send_fd(PRIV_PRIVILEGED, fd);
	if (fd >= 0) close(fd);
}
