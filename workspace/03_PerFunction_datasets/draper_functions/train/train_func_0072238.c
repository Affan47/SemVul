_update_ip4_address (NMDevice *self)
{
	NMDevicePrivate *priv = NM_DEVICE_GET_PRIVATE (self);
	struct ifreq req;
	guint32 new_address;
	int fd;

	g_return_if_fail (self  != NULL);

	fd = socket (PF_INET, SOCK_DGRAM, 0);
	if (fd < 0) {
		nm_log_err (LOGD_IP4, "couldn't open control socket.");
		return;
	}

	memset (&req, 0, sizeof (struct ifreq));
	strncpy (req.ifr_name, nm_device_get_ip_iface (self), IFNAMSIZ);
	if (ioctl (fd, SIOCGIFADDR, &req) == 0) {
		new_address = ((struct sockaddr_in *)(&req.ifr_addr))->sin_addr.s_addr;
		if (new_address != priv->ip4_address)
			priv->ip4_address = new_address;
	}
	close (fd);
}
