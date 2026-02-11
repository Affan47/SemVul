ssd_set_alarm(struct ssd_device *dev)
{
	uint32_t val;

	if (dev->protocol_info.ver <= SSD_PROTOCOL_V3) {
		return;
	}

	val = ssd_reg32_read(dev->ctrlp + SSD_LED_REG);


	val &= ~0x1;

	val |= 0x2;

	ssd_reg32_write(dev->ctrlp + SSD_LED_REG, val);
}
