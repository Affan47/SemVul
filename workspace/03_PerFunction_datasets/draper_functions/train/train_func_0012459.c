snd_mpu401_unregister_all(void)
{
	int i;

	if (pnp_registered)
		pnp_unregister_driver(&snd_mpu401_pnp_driver);
	for (i = 0; i < ARRAY_SIZE(platform_devices); ++i)
		platform_device_unregister(platform_devices[i]);
	platform_driver_unregister(&snd_mpu401_driver);
}
