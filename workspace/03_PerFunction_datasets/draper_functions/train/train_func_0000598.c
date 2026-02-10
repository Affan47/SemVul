sd_wait_voltage_stable_2(struct realtek_pci_sdmmc *host)
{
	struct rtsx_pcr *pcr = host->pcr;
	int err;
	u8 stat, mask, val;


	msleep(50);


	err = rtsx_pci_write_register(pcr, SD_BUS_STAT, 0xFF, SD_CLK_TOGGLE_EN);
	if (err < 0)
		return err;


	msleep(20);


	err = rtsx_pci_read_register(pcr, SD_BUS_STAT, &stat);
	if (err < 0)
		return err;

	mask = SD_CMD_STATUS | SD_DAT3_STATUS | SD_DAT2_STATUS |
		SD_DAT1_STATUS | SD_DAT0_STATUS;
	val = SD_CMD_STATUS | SD_DAT3_STATUS | SD_DAT2_STATUS |
		SD_DAT1_STATUS | SD_DAT0_STATUS;
	if ((stat & mask) != val) {
		dev_dbg(sdmmc_dev(host),
			"%s: SD_BUS_STAT = 0x%x\n", __func__, stat);
		rtsx_pci_write_register(pcr, SD_BUS_STAT,
				SD_CLK_TOGGLE_EN | SD_CLK_FORCE_STOP, 0);
		rtsx_pci_write_register(pcr, CARD_CLK_EN, 0xFF, 0);
		return -EINVAL;
	}

	return 0;
}
