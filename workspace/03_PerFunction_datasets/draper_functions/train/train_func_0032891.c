xhci_mvebu_mbus_init_quirk(struct platform_device *pdev)
{
	struct resource	*res;
	void __iomem *base;
	const struct mbus_dram_target_info *dram;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	if (!res)
		return -ENODEV;


	base = ioremap(res->start, resource_size(res));
	if (!base)
		return -ENODEV;

	dram = mv_mbus_dram_info();
	xhci_mvebu_mbus_config(base, dram);


	iounmap(base);

	return 0;
}
