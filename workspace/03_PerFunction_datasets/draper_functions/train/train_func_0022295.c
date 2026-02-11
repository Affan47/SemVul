proc_get_mac_reg_dump2(char *page, char **start,
			  off_t offset, int count,
			  int *eof, void *data)
{
	struct net_device *dev = data;
	struct adapter *padapter = (struct adapter *)rtw_netdev_priv(dev);
	int len = 0;
	int i, j = 1;

	len += snprintf(page + len, count - len, "\n======= MAC REG =======\n");
	memset(page, 0, count);
	for (i = 0x300; i < 0x600; i += 4) {
		if (j%4 == 1)
			len += snprintf(page + len, count - len, "0x%02x", i);
		len += snprintf(page + len, count - len, " 0x%08x ", usb_read32(padapter, i));
		if ((j++)%4 == 0)
			len += snprintf(page + len, count - len, "\n");
	}

	*eof = 1;
	return len;
}
