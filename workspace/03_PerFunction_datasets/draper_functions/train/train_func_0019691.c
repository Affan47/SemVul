wbsd_write_config(struct wbsd_host *host, u8 reg, u8 value)
{
	BUG_ON(host->config == 0);

	outb(reg, host->config);
	outb(value, host->config + 1);
}
