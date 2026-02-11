sdmmc_execute_tuning(struct mmc_host *mmc, u32 opcode)
{
	struct realtek_pci_sdmmc *host = mmc_priv(mmc);
	struct rtsx_pcr *pcr = host->pcr;
	int err = 0;

	if (host->eject)
		return -ENOMEDIUM;

	err = rtsx_pci_card_exclusive_check(host->pcr, RTSX_SD_CARD);
	if (err)
		return err;

	mutex_lock(&pcr->pcr_mutex);

	rtsx_pci_start_run(pcr);


	switch (mmc->ios.timing) {
	case MMC_TIMING_UHS_SDR104:
		err = sd_change_phase(host, SDR104_TX_PHASE(pcr), false);
		break;

	case MMC_TIMING_UHS_SDR50:
		err = sd_change_phase(host, SDR50_TX_PHASE(pcr), false);
		break;

	case MMC_TIMING_UHS_DDR50:
		err = sd_change_phase(host, DDR50_TX_PHASE(pcr), false);
		break;

	default:
		err = 0;
	}

	if (err)
		goto out;


	if ((mmc->ios.timing == MMC_TIMING_UHS_SDR104) ||
			(mmc->ios.timing == MMC_TIMING_UHS_SDR50))
		err = sd_tuning_rx(host, opcode);
	else if (mmc->ios.timing == MMC_TIMING_UHS_DDR50)
		err = sd_change_phase(host, DDR50_RX_PHASE(pcr), true);

out:
	mutex_unlock(&pcr->pcr_mutex);

	return err;
}
