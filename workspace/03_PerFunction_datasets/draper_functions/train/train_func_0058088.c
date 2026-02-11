skge_init_module(void)
{
	if (dmi_check_system(skge_32bit_dma_boards))
		only_32bit_dma = 1;
	skge_debug_init();
	return pci_register_driver(&skge_driver);
}
