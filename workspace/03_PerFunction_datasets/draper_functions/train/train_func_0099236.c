e100_init_module(void)
{
	if (((1 << debug) - 1) & NETIF_MSG_DRV) {
		pr_info("%s, %s\n", DRV_DESCRIPTION, DRV_VERSION);
		pr_info("%s\n", DRV_COPYRIGHT);
	}
	return pci_register_driver(&e100_driver);
}
