fm_rx_get_rssi_threshold(struct fmdev *fmdev, short *curr_rssi_lvl)
{
	if (fmdev->curr_fmmode != FM_MODE_RX)
		return -EPERM;

	if (curr_rssi_lvl == NULL) {
		fmerr("Invalid memory\n");
		return -ENOMEM;
	}

	*curr_rssi_lvl = fmdev->rx.rssi_threshold;

	return 0;
}
