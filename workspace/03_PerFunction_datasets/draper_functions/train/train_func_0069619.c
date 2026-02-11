sdricoh_reset(struct sdricoh_host *host)
{
	dev_dbg(host->dev, "reset\n");
	sdricoh_writel(host, R2F0_RESET, 0x10001);
	sdricoh_writel(host, R2E0_INIT, 0x10000);
	if (sdricoh_readl(host, R2E0_INIT) != 0x10000)
		return -EIO;
	sdricoh_writel(host, R2E0_INIT, 0x10007);

	sdricoh_writel(host, R224_MODE, 0x2000000);
	sdricoh_writel(host, R228_POWER, 0xe0);


	sdricoh_writel(host, R21C_STATUS, 0x18);

	return 0;
}
