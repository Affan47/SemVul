bnep_connadd(int sk, uint16_t role, char *dev)
{
	struct bnep_connadd_req req;

	strncpy(req.device, dev, 16);
	req.device[15] = '\0';
	req.sock = sk;
	req.role = role;
	if (ioctl(ctl, bnepconnadd, &req))
		return -1;
	strncpy(dev, req.device, 16);
	return 0;
}
