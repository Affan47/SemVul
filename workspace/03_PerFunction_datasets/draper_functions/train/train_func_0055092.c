br2684_create_iface (NMDeviceAdsl *self, NMSettingAdsl *s_adsl)
{
	NMDeviceAdslPrivate *priv = NM_DEVICE_ADSL_GET_PRIVATE (self);
	const char *iface = nm_device_get_iface (NM_DEVICE (self));
	struct atm_newif_br2684 ni;
	int err, fd;
	gboolean success = FALSE;
	guint num = 0;

	g_return_val_if_fail (s_adsl != NULL, FALSE);

	fd = socket (PF_ATMPVC, SOCK_DGRAM, ATM_AAL5);
	if (fd < 0) {
		nm_log_err (LOGD_ADSL, "(%s): failed to open ATM control socket (%d)",
		            iface, errno);
		return FALSE;
	}

	memset (&ni, 0, sizeof (ni));
	ni.backend_num = ATM_BACKEND_BR2684;
	ni.media = BR2684_MEDIA_ETHERNET;
	ni.mtu = 1500;


	while (num < 10000) {
		memset (&ni.ifname, 0, sizeof (ni.ifname));
		snprintf (ni.ifname, sizeof (ni.ifname), "nas%d", num);

		err = ioctl (fd, ATM_NEWBACKENDIF, &ni);
		if (err == 0) {
			set_nas_iface (self, -1, ni.ifname);
			nm_log_info (LOGD_ADSL, "(%s): using NAS interface %s (%d)",
			             iface, priv->nas_ifname, priv->nas_ifindex);
			success = TRUE;
			break;
		} else if (errno == -EEXIST) {

			num++;
		} else {
			nm_log_warn (LOGD_ADSL, "(%s): failed to create br2684 interface (%d)",
			             iface, errno);
			break;
		}
	}

	close (fd);
	return success;
}
