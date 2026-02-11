sd_set_bus_speed_mode(struct mmc_card *card, u8 *status)
{
	int err;
	unsigned int timing = 0;

	switch (card->sd_bus_speed) {
	case UHS_SDR104_BUS_SPEED:
		timing = MMC_TIMING_UHS_SDR104;
		card->sw_caps.uhs_max_dtr = UHS_SDR104_MAX_DTR;
		break;
	case UHS_DDR50_BUS_SPEED:
		timing = MMC_TIMING_UHS_DDR50;
		card->sw_caps.uhs_max_dtr = UHS_DDR50_MAX_DTR;
		break;
	case UHS_SDR50_BUS_SPEED:
		timing = MMC_TIMING_UHS_SDR50;
		card->sw_caps.uhs_max_dtr = UHS_SDR50_MAX_DTR;
		break;
	case UHS_SDR25_BUS_SPEED:
		timing = MMC_TIMING_UHS_SDR25;
		card->sw_caps.uhs_max_dtr = UHS_SDR25_MAX_DTR;
		break;
	case UHS_SDR12_BUS_SPEED:
		timing = MMC_TIMING_UHS_SDR12;
		card->sw_caps.uhs_max_dtr = UHS_SDR12_MAX_DTR;
		break;
	default:
		return 0;
	}

	err = mmc_sd_switch(card, 1, 0, card->sd_bus_speed, status);
	if (err)
		return err;

	if ((status[16] & 0xF) != card->sd_bus_speed)
		pr_warn("%s: Problem setting bus speed mode!\n",
			mmc_hostname(card->host));
	else {
		mmc_set_timing(card->host, timing);
		mmc_set_clock(card->host, card->sw_caps.uhs_max_dtr);
	}

	return 0;
}
