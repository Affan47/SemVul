ssd_bm_enter_cap_learning(struct ssd_device *dev)
{
	uint16_t buf = SSD_BM_ENTER_CAP_LEARNING;
	uint8_t cmd = SSD_BM_MANUFACTURERACCESS;
	int ret;

	ret = ssd_smbus_write_word(dev, SSD_BM_SLAVE_ADDRESS, cmd, (uint8_t *)&buf);
	if (ret) {
		goto out;
	}

out:
	return ret;
}
