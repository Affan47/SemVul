sd_set_bus_width(struct rtsx_usb_sdmmc *host,
		unsigned char bus_width)
{
	int err = 0;
	u8 width[] = {
		[MMC_BUS_WIDTH_1] = SD_BUS_WIDTH_1BIT,
		[MMC_BUS_WIDTH_4] = SD_BUS_WIDTH_4BIT,
		[MMC_BUS_WIDTH_8] = SD_BUS_WIDTH_8BIT,
	};

	if (bus_width <= MMC_BUS_WIDTH_8)
		err = rtsx_usb_write_register(host->ucr, SD_CFG1,
				0x03, width[bus_width]);

	return err;
}
