bnep_kill_connection(bdaddr_t *dst)
{
	struct bnep_conndel_req req;

	memset(&req, 0, sizeof(req));
	baswap((bdaddr_t *)&req.dst, dst);
	req.flags = 0;
	if (ioctl(ctl, BNEPCONNDEL, &req)) {
		int err = -errno;
		error("Failed to kill connection: %s (%d)",
						strerror(-err), -err);
		return err;
	}
	return 0;
}
