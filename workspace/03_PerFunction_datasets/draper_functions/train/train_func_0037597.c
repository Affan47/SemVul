mvs_64xx_spi_waitdataready(struct mvs_info *mvi, u32 timeout)
{
	void __iomem *regs = mvi->regs_ex;
	u32 i, dwTmp;

	for (i = 0; i < timeout; i++) {
		dwTmp = ior32(SPI_CTRL_REG_64XX);
		if (!(dwTmp & SPI_CTRL_SPISTART))
			return 0;
		msleep(10);
	}

	return -1;
}
