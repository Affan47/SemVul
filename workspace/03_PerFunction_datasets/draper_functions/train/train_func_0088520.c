ssd_set_flush_timeout(struct ssd_device *dev, int m)
{
	uint32_t to;
	uint32_t val = 0;

	if (dev->protocol_info.ver < SSD_PROTOCOL_V3_1_1) {
		return;
	}

	switch(m) {
		case SSD_WMODE_BUFFER:
			to = SSD_WMODE_BUFFER_TIMEOUT;
			break;
		case SSD_WMODE_BUFFER_EX:
			if (dev->protocol_info.ver < SSD_PROTOCOL_V3_2_1) {
				to = SSD_WMODE_BUFFER_EX_TIMEOUT;
			} else {
				to = SSD_WMODE_BUFFER_TIMEOUT;
			}
			break;
		case SSD_WMODE_FUA:
			to = SSD_WMODE_FUA_TIMEOUT;
			break;
		default:
			return;
	}

	val = (((uint32_t)((uint32_t)m & 0x3) << 28) | to);

	ssd_reg32_write(dev->ctrlp + SSD_FLUSH_TIMEOUT_REG, val);
}
