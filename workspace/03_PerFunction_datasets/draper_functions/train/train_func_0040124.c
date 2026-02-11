ssd_check_reset_sync(struct ssd_device *dev)
{
	uint32_t val;

	if (dev->protocol_info.ver < SSD_PROTOCOL_V3_1_3) {
		return 0;
	}

	val = ssd_reg32_read(dev->ctrlp + SSD_HW_STATUS_REG);
	if (!((val >> 8) & 0x1)) {

		hio_warn("%s: controller state error: %#x\n", dev->name, val);
		return -1;
	}

	if (dev->protocol_info.ver < SSD_PROTOCOL_V3_2) {
		return 0;
	}

	if (((val >> 9 ) & 0x1)) {
		hio_warn("%s: controller reset asynchronously: %#x\n", dev->name, val);
		ssd_gen_swlog(dev, SSD_LOG_CTRL_RST_SYNC, val);
		return -1;
	}

	return 0;
}
