omap_hsmmc_set_bus_mode(struct omap_hsmmc_host *host)
{
	struct mmc_ios *ios = &host->mmc->ios;
	u32 con;

	con = OMAP_HSMMC_READ(host->base, CON);
	if (ios->bus_mode == MMC_BUSMODE_OPENDRAIN)
		OMAP_HSMMC_WRITE(host->base, CON, con | OD);
	else
		OMAP_HSMMC_WRITE(host->base, CON, con & ~OD);
}
