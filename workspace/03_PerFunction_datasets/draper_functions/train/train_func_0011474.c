qla2x00_read_flash_data(struct qla_hw_data *ha, uint8_t *tmp_buf,
	uint32_t saddr, uint32_t length)
{
	struct device_reg_2xxx __iomem *reg = &ha->iobase->isp;
	uint32_t midpoint, ilength;
	uint8_t data;

	midpoint = length / 2;

	WRT_REG_WORD(&reg->nvram, 0);
	RD_REG_WORD(&reg->nvram);
	for (ilength = 0; ilength < length; saddr++, ilength++, tmp_buf++) {
		if (ilength == midpoint) {
			WRT_REG_WORD(&reg->nvram, NVR_SELECT);
			RD_REG_WORD(&reg->nvram);
		}
		data = qla2x00_read_flash_byte(ha, saddr);
		if (saddr % 100)
			udelay(10);
		*tmp_buf = data;
		cond_resched();
	}
}
