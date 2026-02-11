qla24xx_pause_risc(struct device_reg_24xx __iomem *reg, struct qla_hw_data *ha)
{
	WRT_REG_DWORD(&reg->hccr, HCCRX_SET_RISC_PAUSE);


	udelay(100);
	if (RD_REG_DWORD(&reg->host_status) & HSRX_RISC_PAUSED)
		set_bit(RISC_PAUSE_CMPL, &ha->fw_dump_cap_flags);
}
