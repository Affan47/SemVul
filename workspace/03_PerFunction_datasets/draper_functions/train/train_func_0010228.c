fm_drv_init(void)
{
	struct fmdev *fmdev = NULL;
	int ret = -ENOMEM;

	fmdbg("FM driver version %s\n", FM_DRV_VERSION);

	fmdev = kzalloc(sizeof(struct fmdev), GFP_KERNEL);
	if (NULL == fmdev) {
		fmerr("Can't allocate operation structure memory\n");
		return ret;
	}
	fmdev->rx.rds.buf_size = default_rds_buf * FM_RDS_BLK_SIZE;
	fmdev->rx.rds.buff = kzalloc(fmdev->rx.rds.buf_size, GFP_KERNEL);
	if (NULL == fmdev->rx.rds.buff) {
		fmerr("Can't allocate rds ring buffer\n");
		goto rel_dev;
	}

	ret = fm_v4l2_init_video_device(fmdev, radio_nr);
	if (ret < 0)
		goto rel_rdsbuf;

	fmdev->irq_info.handlers = int_handler_table;
	fmdev->curr_fmmode = FM_MODE_OFF;
	fmdev->tx_data.pwr_lvl = FM_PWR_LVL_DEF;
	fmdev->tx_data.preemph = FM_TX_PREEMPH_50US;
	return ret;

rel_rdsbuf:
	kfree(fmdev->rx.rds.buff);
rel_dev:
	kfree(fmdev);

	return ret;
}
