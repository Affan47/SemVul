flexfb_init(void)
{
	int ret, ret2;

	ret = spi_register_driver(&flexfb_spi_driver);
	ret2 = platform_driver_register(&flexfb_platform_driver);
	if (ret < 0)
		return ret;
	return ret2;
}
