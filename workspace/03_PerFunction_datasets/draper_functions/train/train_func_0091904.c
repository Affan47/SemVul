mmc_can_reset(struct mmc_card *card)
{
	u8 rst_n_function;

	rst_n_function = card->ext_csd.rst_n_function;
	if ((rst_n_function & EXT_CSD_RST_N_EN_MASK) != EXT_CSD_RST_N_ENABLED)
		return 0;
	return 1;
}
