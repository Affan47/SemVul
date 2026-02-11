pcie_portdrv_init(void)
{
	int retval;

	if (pcie_ports_disabled)
		return pci_register_driver(&pcie_portdriver);

	dmi_check_system(pcie_portdrv_dmi_table);

	retval = pcie_port_bus_register();
	if (retval) {
		printk(KERN_WARNING "PCIE: bus_register error: %d\n", retval);
		goto out;
	}
	retval = pci_register_driver(&pcie_portdriver);
	if (retval)
		pcie_port_bus_unregister();
 out:
	return retval;
}
