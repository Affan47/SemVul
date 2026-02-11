qlcnic_83xx_check_cmd_peg_status(struct qlcnic_adapter *p_dev)
{
	int retries = QLCNIC_CMDPEG_CHECK_RETRY_COUNT;
	u32 val;

	do {
		val = QLC_SHARED_REG_RD32(p_dev, QLCNIC_CMDPEG_STATE);
		if (val == QLC_83XX_CMDPEG_COMPLETE)
			return 0;
		msleep(QLCNIC_CMDPEG_CHECK_DELAY);
	} while (--retries);

	dev_err(&p_dev->pdev->dev, "%s: failed, state = 0x%x\n", __func__, val);
	return -EIO;
}
