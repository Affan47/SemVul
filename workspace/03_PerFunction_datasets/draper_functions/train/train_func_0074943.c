bcma_release_core_dev(struct device *dev)
{
	struct bcma_device *core = container_of(dev, struct bcma_device, dev);
	if (core->io_addr)
		iounmap(core->io_addr);
	if (core->io_wrap)
		iounmap(core->io_wrap);
	kfree(core);
}
