mchip_take_picture(void)
{
	int i;

	mchip_hic_stop();
	mchip_subsample();
	mchip_dma_setup(meye.mchip_dmahandle);

	mchip_set(MCHIP_HIC_MODE, MCHIP_HIC_MODE_STILL_CAP);
	mchip_set(MCHIP_HIC_CMD, MCHIP_HIC_CMD_START);

	mchip_delay(MCHIP_HIC_CMD, 0);

	for (i = 0; i < 100; ++i) {
		if (mchip_delay(MCHIP_HIC_STATUS, MCHIP_HIC_STATUS_IDLE))
			break;
		msleep(1);
	}
}
