qxl_init(void)
{
#ifdef CONFIG_VGA_CONSOLE
	if (vgacon_text_force() && qxl_modeset == -1)
		return -EINVAL;
#endif

	if (qxl_modeset == 0)
		return -EINVAL;
	qxl_driver.num_ioctls = qxl_max_ioctls;
	return drm_pci_init(&qxl_driver, &qxl_pci_driver);
}
