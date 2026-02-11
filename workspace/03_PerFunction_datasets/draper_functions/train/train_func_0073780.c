smsc911x_soft_reset(struct smsc911x_data *pdata)
{
	unsigned int timeout;
	unsigned int temp;
	int ret;


	ret = smsc911x_phy_general_power_up(pdata);
	if (ret) {
		SMSC_WARN(pdata, drv, "Failed to power-up the PHY chip");
		return ret;
	}


	if (pdata->generation == 4) {
		ret = smsc911x_phy_disable_energy_detect(pdata);

		if (ret) {
			SMSC_WARN(pdata, drv, "Failed to wakeup the PHY chip");
			return ret;
		}
	}


	smsc911x_reg_write(pdata, HW_CFG, HW_CFG_SRST_);
	timeout = 10;
	do {
		udelay(10);
		temp = smsc911x_reg_read(pdata, HW_CFG);
	} while ((--timeout) && (temp & HW_CFG_SRST_));

	if (unlikely(temp & HW_CFG_SRST_)) {
		SMSC_WARN(pdata, drv, "Failed to complete reset");
		return -EIO;
	}

	if (pdata->generation == 4) {
		ret = smsc911x_phy_enable_energy_detect(pdata);

		if (ret) {
			SMSC_WARN(pdata, drv, "Failed to wakeup the PHY chip");
			return ret;
		}
	}

	return 0;
}
