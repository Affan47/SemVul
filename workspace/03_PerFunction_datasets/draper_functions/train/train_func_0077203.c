zt5550_init(void)
{
	struct resource *r;
	int rc;

	info(DRIVER_DESC " version: " DRIVER_VERSION);
	r = request_region(ENUM_PORT, 1, "#ENUM hotswap signal register");
	if (!r)
		return -EBUSY;

	rc = pci_register_driver(&zt5550_hc_driver);
	if (rc < 0)
		release_region(ENUM_PORT, 1);
	return rc;
}
