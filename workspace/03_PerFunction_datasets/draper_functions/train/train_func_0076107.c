bnep_connadd(int sk, uint16_t role, char *dev)
{
	struct bnep_connadd_req req;

	memset(&req, 0, sizeof(req));
	strncpy(req.device, dev, 16);
	req.device[15] = '\0';
	req.sock = sk;
	req.role = role;
	if (ioctl(ctl, BNEPCONNADD, &req) < 0) {
		int err = -errno;
		error("Failed to add device %s: %s(%d)",
				dev, strerror(-err), -err);
		return err;
	}

	strncpy(dev, req.device, 16);
	return 0;
}
