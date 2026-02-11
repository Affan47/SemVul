bcma_host_soc_init(struct bcma_soc *soc)
{
	struct bcma_bus *bus = &soc->bus;
	int err;


	err = bcma_bus_early_register(bus);
	if (err)
		iounmap(bus->mmio);

	return err;
}
