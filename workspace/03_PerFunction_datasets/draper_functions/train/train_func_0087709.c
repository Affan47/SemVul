read_file_misc(struct file *file, char __user *user_buf,
				   size_t count, loff_t *ppos)
{
	struct ath5k_hw *ah = file->private_data;
	char buf[700];
	unsigned int len = 0;
	u32 filt = ath5k_hw_get_rx_filter(ah);

	len += snprintf(buf + len, sizeof(buf) - len, "bssid-mask: %pM\n",
			ah->bssidmask);
	len += snprintf(buf + len, sizeof(buf) - len, "filter-flags: 0x%x ",
			filt);
	if (filt & AR5K_RX_FILTER_UCAST)
		len += snprintf(buf + len, sizeof(buf) - len, " UCAST");
	if (filt & AR5K_RX_FILTER_MCAST)
		len += snprintf(buf + len, sizeof(buf) - len, " MCAST");
	if (filt & AR5K_RX_FILTER_BCAST)
		len += snprintf(buf + len, sizeof(buf) - len, " BCAST");
	if (filt & AR5K_RX_FILTER_CONTROL)
		len += snprintf(buf + len, sizeof(buf) - len, " CONTROL");
	if (filt & AR5K_RX_FILTER_BEACON)
		len += snprintf(buf + len, sizeof(buf) - len, " BEACON");
	if (filt & AR5K_RX_FILTER_PROM)
		len += snprintf(buf + len, sizeof(buf) - len, " PROM");
	if (filt & AR5K_RX_FILTER_XRPOLL)
		len += snprintf(buf + len, sizeof(buf) - len, " XRPOLL");
	if (filt & AR5K_RX_FILTER_PROBEREQ)
		len += snprintf(buf + len, sizeof(buf) - len, " PROBEREQ");
	if (filt & AR5K_RX_FILTER_PHYERR_5212)
		len += snprintf(buf + len, sizeof(buf) - len, " PHYERR-5212");
	if (filt & AR5K_RX_FILTER_RADARERR_5212)
		len += snprintf(buf + len, sizeof(buf) - len, " RADARERR-5212");
	if (filt & AR5K_RX_FILTER_PHYERR_5211)
		snprintf(buf + len, sizeof(buf) - len, " PHYERR-5211");
	if (filt & AR5K_RX_FILTER_RADARERR_5211)
		len += snprintf(buf + len, sizeof(buf) - len, " RADARERR-5211");

	len += snprintf(buf + len, sizeof(buf) - len, "\nopmode: %s (%d)\n",
			ath_opmode_to_string(ah->opmode), ah->opmode);

	if (len > sizeof(buf))
		len = sizeof(buf);

	return simple_read_from_buffer(user_buf, count, ppos, buf, len);
}
