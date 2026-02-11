qla24xx_read_flash_dword(struct qla_hw_data *ha, uint32_t addr)
{
	int rval;
	uint32_t cnt, data;
	struct device_reg_24xx __iomem *reg = &ha->iobase->isp24;

	WRT_REG_DWORD(&reg->flash_addr, addr & ~FARX_DATA_FLAG);

	rval = QLA_SUCCESS;
	for (cnt = 3000;
	    (RD_REG_DWORD(&reg->flash_addr) & FARX_DATA_FLAG) == 0 &&
	    rval == QLA_SUCCESS; cnt--) {
		if (cnt)
			udelay(10);
		else
			rval = QLA_FUNCTION_TIMEOUT;
		cond_resched();
	}


	data = 0xDEADDEAD;
	if (rval == QLA_SUCCESS)
		data = RD_REG_DWORD(&reg->flash_data);

	return data;
}
