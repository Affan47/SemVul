fm_rx_set_rds_system(struct fmdev *fmdev, u8 rds_mode)
{
	u16 payload;
	int ret;

	if (fmdev->curr_fmmode != FM_MODE_RX)
		return -EPERM;

	if (rds_mode != FM_RDS_SYSTEM_RDS && rds_mode != FM_RDS_SYSTEM_RBDS) {
		fmerr("Invalid rds mode\n");
		return -EINVAL;
	}

	payload = (u16)rds_mode;
	ret = fmc_send_cmd(fmdev, RDS_SYSTEM_SET, REG_WR, &payload,
			sizeof(payload), NULL, NULL);
	if (ret < 0)
		return ret;

	fmdev->rx.rds_mode = rds_mode;

	return 0;
}
