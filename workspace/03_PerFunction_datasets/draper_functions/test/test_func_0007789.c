i7core_pci_ctl_create(struct i7core_pvt *pvt)
{
	pvt->i7core_pci = edac_pci_create_generic_ctl(
						&pvt->i7core_dev->pdev[0]->dev,
						EDAC_MOD_STR);
	if (unlikely(!pvt->i7core_pci))
		i7core_printk(KERN_WARNING,
			      "Unable to setup PCI error report via EDAC\n");
}
