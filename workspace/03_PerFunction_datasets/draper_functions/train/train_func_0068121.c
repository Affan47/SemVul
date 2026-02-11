net_add (NMUdevManager *self, GUdevDevice *udev_device)
{
	gint ifindex = -1;
	gint etype;
	const char *ifname = NULL, *path = NULL, *tmp;
	char *driver = NULL;
	gboolean is_ctc;

	g_return_if_fail (udev_device != NULL);

	if (!dev_get_attrs (udev_device, &ifname, &path, &driver, &ifindex))
		return;

	if (ifindex < 0) {
		nm_log_warn (LOGD_HW, "%s: device had invalid ifindex %d; ignoring...", path, ifindex);
		goto out;
	}

	etype = g_udev_device_get_sysfs_attr_as_int (udev_device, "type");
	is_ctc = (strncmp (ifname, "ctc", 3) == 0) && (etype == 256);


	if ((etype != ARPHRD_ETHER) && (etype != ARPHRD_INFINIBAND) && (is_ctc == FALSE)) {
		nm_log_dbg (LOGD_HW, "(%s): ignoring interface with type %d", ifname, etype);
		goto out;
	}


	tmp = g_udev_device_get_property (udev_device, "DEVTYPE");
	if (g_strcmp0 (tmp, "wwan") == 0) {
		nm_log_dbg (LOGD_HW, "(%s): ignoring interface with devtype '%s'", ifname, tmp);
		goto out;
	}

	g_signal_emit (self, signals[DEVICE_ADDED], 0, udev_device, ifname, path, driver, ifindex);

out:
	g_free (driver);
}
