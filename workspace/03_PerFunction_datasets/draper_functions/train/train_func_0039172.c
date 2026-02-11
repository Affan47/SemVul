sdhci_set_power(struct sdhci_host *host, unsigned char mode,
			    unsigned short vdd)
{
	struct mmc_host *mmc = host->mmc;
	u8 pwr = 0;

	if (!IS_ERR(mmc->supply.vmmc)) {
		spin_unlock_irq(&host->lock);
		mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, vdd);
		spin_lock_irq(&host->lock);

		if (mode != MMC_POWER_OFF)
			sdhci_writeb(host, SDHCI_POWER_ON, SDHCI_POWER_CONTROL);
		else
			sdhci_writeb(host, 0, SDHCI_POWER_CONTROL);

		return;
	}

	if (mode != MMC_POWER_OFF) {
		switch (1 << vdd) {
		case MMC_VDD_165_195:
			pwr = SDHCI_POWER_180;
			break;
		case MMC_VDD_29_30:
		case MMC_VDD_30_31:
			pwr = SDHCI_POWER_300;
			break;
		case MMC_VDD_32_33:
		case MMC_VDD_33_34:
			pwr = SDHCI_POWER_330;
			break;
		default:
			WARN(1, "%s: Invalid vdd %#x\n",
			     mmc_hostname(host->mmc), vdd);
			break;
		}
	}

	if (host->pwr == pwr)
		return;

	host->pwr = pwr;

	if (pwr == 0) {
		sdhci_writeb(host, 0, SDHCI_POWER_CONTROL);
		if (host->quirks2 & SDHCI_QUIRK2_CARD_ON_NEEDS_BUS_ON)
			sdhci_runtime_pm_bus_off(host);
		vdd = 0;
	} else {


		if (!(host->quirks & SDHCI_QUIRK_SINGLE_POWER_WRITE))
			sdhci_writeb(host, 0, SDHCI_POWER_CONTROL);


		if (host->quirks & SDHCI_QUIRK_NO_SIMULT_VDD_AND_POWER)
			sdhci_writeb(host, pwr, SDHCI_POWER_CONTROL);

		pwr |= SDHCI_POWER_ON;

		sdhci_writeb(host, pwr, SDHCI_POWER_CONTROL);

		if (host->quirks2 & SDHCI_QUIRK2_CARD_ON_NEEDS_BUS_ON)
			sdhci_runtime_pm_bus_on(host);


		if (host->quirks & SDHCI_QUIRK_DELAY_AFTER_POWER)
			mdelay(10);
	}
}
