sdmmc_set_ios(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct rtsx_usb_sdmmc *host = mmc_priv(mmc);
	struct rtsx_ucr *ucr = host->ucr;

	dev_dbg(sdmmc_dev(host), "%s\n", __func__);
	mutex_lock(&ucr->dev_mutex);

	sd_set_power_mode(host, ios->power_mode);
	sd_set_bus_width(host, ios->bus_width);
	sd_set_timing(host, ios->timing, &host->ddr_mode);

	host->vpclk = false;
	host->double_clk = true;

	switch (ios->timing) {
	case MMC_TIMING_UHS_SDR104:
	case MMC_TIMING_UHS_SDR50:
		host->ssc_depth = SSC_DEPTH_2M;
		host->vpclk = true;
		host->double_clk = false;
		break;
	case MMC_TIMING_UHS_DDR50:
	case MMC_TIMING_UHS_SDR25:
		host->ssc_depth = SSC_DEPTH_1M;
		break;
	default:
		host->ssc_depth = SSC_DEPTH_512K;
		break;
	}

	host->initial_mode = (ios->clock <= 1000000) ? true : false;
	host->clock = ios->clock;

	rtsx_usb_switch_clock(host->ucr, host->clock, host->ssc_depth,
			host->initial_mode, host->double_clk, host->vpclk);

	mutex_unlock(&ucr->dev_mutex);
	dev_dbg(sdmmc_dev(host), "%s end\n", __func__);
}
