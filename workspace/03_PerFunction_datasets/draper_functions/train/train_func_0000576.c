fm_tx_set_region(struct fmdev *fmdev, u8 region)
{
	u16 payload;
	int ret;

	if (region != FM_BAND_EUROPE_US && region != FM_BAND_JAPAN) {
		fmerr("Invalid band\n");
		return -EINVAL;
	}


	payload = (u16)region;
	ret = fmc_send_cmd(fmdev, TX_BAND_SET, REG_WR, &payload,
			sizeof(payload), NULL, NULL);
	if (ret < 0)
		return ret;

	return 0;
}
