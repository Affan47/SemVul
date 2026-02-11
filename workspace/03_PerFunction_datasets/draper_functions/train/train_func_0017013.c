orinoco_add_hostscan_results(struct orinoco_private *priv,
				  unsigned char *buf,
				  size_t len)
{
	int offset;
	size_t atom_len;
	bool abort = false;

	switch (priv->firmware_type) {
	case FIRMWARE_TYPE_AGERE:
		atom_len = sizeof(struct agere_scan_apinfo);
		offset = 0;
		break;

	case FIRMWARE_TYPE_SYMBOL:


		if (len % 76)
			atom_len = 68;
		else if (len % 68)
			atom_len = 76;
		else if (len >= 1292 && buf[68] == 0)
			atom_len = 76;
		else
			atom_len = 68;
		offset = 0;
		break;

	case FIRMWARE_TYPE_INTERSIL:
		offset = 4;
		if (priv->has_hostscan) {
			atom_len = le16_to_cpup((__le16 *)buf);

			if (atom_len < sizeof(struct prism2_scan_apinfo)) {
				printk(KERN_ERR "%s: Invalid atom_len in scan "
				       "data: %zu\n", priv->ndev->name,
				       atom_len);
				abort = true;
				goto scan_abort;
			}
		} else
			atom_len = offsetof(struct prism2_scan_apinfo, atim);
		break;

	default:
		abort = true;
		goto scan_abort;
	}


	if ((len - offset) % atom_len) {
		printk(KERN_ERR "%s: Unexpected scan data length %zu, "
		       "atom_len %zu, offset %d\n", priv->ndev->name, len,
		       atom_len, offset);
		abort = true;
		goto scan_abort;
	}


	for (; offset + atom_len <= len; offset += atom_len) {
		union hermes_scan_info *atom;

		atom = (union hermes_scan_info *) (buf + offset);

		orinoco_add_hostscan_result(priv, atom);
	}

 scan_abort:
	if (priv->scan_request) {
		cfg80211_scan_done(priv->scan_request, abort);
		priv->scan_request = NULL;
	}
}
