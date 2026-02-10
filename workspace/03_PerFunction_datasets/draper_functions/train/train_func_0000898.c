qla2x00_read_optrom_data(struct scsi_qla_host *vha, uint8_t *buf,
    uint32_t offset, uint32_t length)
{
	uint32_t addr, midpoint;
	uint8_t *data;
	struct qla_hw_data *ha = vha->hw;
	struct device_reg_2xxx __iomem *reg = &ha->iobase->isp;


	qla2x00_suspend_hba(vha);


	midpoint = ha->optrom_size / 2;

	qla2x00_flash_enable(ha);
	WRT_REG_WORD(&reg->nvram, 0);
	RD_REG_WORD(&reg->nvram);
	for (addr = offset, data = buf; addr < length; addr++, data++) {
		if (addr == midpoint) {
			WRT_REG_WORD(&reg->nvram, NVR_SELECT);
			RD_REG_WORD(&reg->nvram);
		}

		*data = qla2x00_read_flash_byte(ha, addr);
	}
	qla2x00_flash_disable(ha);


	qla2x00_resume_hba(vha);

	return buf;
}
