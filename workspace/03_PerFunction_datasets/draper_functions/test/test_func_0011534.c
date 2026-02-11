pcifront_init(void)
{
	if (!xen_pv_domain() || xen_initial_domain())
		return -ENODEV;

	if (!xen_has_pv_devices())
		return -ENODEV;

	pci_frontend_registrar(1 );

	return xenbus_register_frontend(&xenpci_driver);
}
