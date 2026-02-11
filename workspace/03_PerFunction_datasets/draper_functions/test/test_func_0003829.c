ingenic_early_console_setup_clock(struct earlycon_device *dev)
{
	void *fdt = initial_boot_params;
	const __be32 *prop;
	int offset;

	offset = fdt_path_offset(fdt, "/ext");
	if (offset < 0)
		return;

	prop = fdt_getprop(fdt, offset, "clock-frequency", NULL);
	if (!prop)
		return;

	dev->port.uartclk = be32_to_cpup(prop);
}
