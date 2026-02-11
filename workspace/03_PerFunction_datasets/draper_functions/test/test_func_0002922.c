dma_bus_init(void)
{
	int err = dmaengine_init_unmap_pool();

	if (err)
		return err;
	return class_register(&dma_devclass);
}
