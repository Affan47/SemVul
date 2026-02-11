sh_msiof_spi_set_pin_regs(struct sh_msiof_spi_priv *p,
				      u32 cpol, u32 cpha,
				      u32 tx_hi_z, u32 lsb_first, u32 cs_high)
{
	u32 tmp;
	int edge;


	tmp = MDR1_SYNCMD_SPI | 1 << MDR1_FLD_SHIFT | MDR1_XXSTP;
	tmp |= !cs_high << MDR1_SYNCAC_SHIFT;
	tmp |= lsb_first << MDR1_BITLSB_SHIFT;
	tmp |= sh_msiof_spi_get_dtdl_and_syncdl(p);
	sh_msiof_write(p, TMDR1, tmp | MDR1_TRMD | TMDR1_PCON);
	if (p->chipdata->master_flags & SPI_MASTER_MUST_TX) {

		tmp &= ~0x0000ffff;
	}
	sh_msiof_write(p, RMDR1, tmp);

	tmp = 0;
	tmp |= CTR_TSCKIZ_SCK | cpol << CTR_TSCKIZ_POL_SHIFT;
	tmp |= CTR_RSCKIZ_SCK | cpol << CTR_RSCKIZ_POL_SHIFT;

	edge = cpol ^ !cpha;

	tmp |= edge << CTR_TEDG_SHIFT;
	tmp |= edge << CTR_REDG_SHIFT;
	tmp |= tx_hi_z ? CTR_TXDIZ_HIZ : CTR_TXDIZ_LOW;
	sh_msiof_write(p, CTR, tmp);
}
