ssd_init_protocol_info(struct ssd_device *dev)
{
	uint32_t val;

	val = ssd_reg32_read(dev->ctrlp + SSD_PROTOCOL_VER_REG);
	if (val == (uint32_t)-1) {
		hio_warn("%s: protocol version error: %#x\n", dev->name, val);
		return -EINVAL;
	}
	dev->protocol_info.ver = val;

	if (dev->protocol_info.ver < SSD_PROTOCOL_V3) {
		dev->protocol_info.init_state_reg = SSD_INIT_STATE_REG0;
		dev->protocol_info.init_state_reg_sz = SSD_INIT_STATE_REG_SZ;

		dev->protocol_info.chip_info_reg = SSD_CHIP_INFO_REG0;
		dev->protocol_info.chip_info_reg_sz = SSD_CHIP_INFO_REG_SZ;
	} else {
		dev->protocol_info.init_state_reg = SSD_PV3_INIT_STATE_REG0;
		dev->protocol_info.init_state_reg_sz = SSD_PV3_INIT_STATE_REG_SZ;

		dev->protocol_info.chip_info_reg = SSD_PV3_CHIP_INFO_REG0;
		dev->protocol_info.chip_info_reg_sz = SSD_PV3_CHIP_INFO_REG_SZ;
	}

	return 0;
}
