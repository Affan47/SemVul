lbtf_beacon_set(struct lbtf_private *priv, struct sk_buff *beacon)
{
	struct cmd_ds_802_11_beacon_set cmd;
	int size;

	lbtf_deb_enter(LBTF_DEB_CMD);

	if (beacon->len > MRVL_MAX_BCN_SIZE) {
		lbtf_deb_leave_args(LBTF_DEB_CMD, "ret %d", -1);
		return -1;
	}
	size =  sizeof(cmd) - sizeof(cmd.beacon) + beacon->len;
	cmd.hdr.size = cpu_to_le16(size);
	cmd.len = cpu_to_le16(beacon->len);
	memcpy(cmd.beacon, (u8 *) beacon->data, beacon->len);

	lbtf_cmd_async(priv, CMD_802_11_BEACON_SET, &cmd.hdr, size);

	lbtf_deb_leave_args(LBTF_DEB_CMD, "ret %d", 0);
	return 0;
}
