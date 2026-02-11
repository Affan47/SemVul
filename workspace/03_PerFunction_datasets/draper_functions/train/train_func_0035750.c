asd_map_memio(struct asd_ha_struct *asd_ha)
{
	int err, i;
	struct asd_ha_addrspace *io_handle;

	asd_ha->iospace = 0;
	for (i = 0; i < 3; i += 2) {
		io_handle = &asd_ha->io_handle[i==0?0:1];
		io_handle->start = pci_resource_start(asd_ha->pcidev, i);
		io_handle->len   = pci_resource_len(asd_ha->pcidev, i);
		io_handle->flags = pci_resource_flags(asd_ha->pcidev, i);
		err = -ENODEV;
		if (!io_handle->start || !io_handle->len) {
			asd_printk("MBAR%d start or length for %s is 0.\n",
				   i==0?0:1, pci_name(asd_ha->pcidev));
			goto Err;
		}
		err = pci_request_region(asd_ha->pcidev, i, ASD_DRIVER_NAME);
		if (err) {
			asd_printk("couldn't reserve memory region for %s\n",
				   pci_name(asd_ha->pcidev));
			goto Err;
		}
		io_handle->addr = ioremap(io_handle->start, io_handle->len);
		if (!io_handle->addr) {
			asd_printk("couldn't map MBAR%d of %s\n", i==0?0:1,
				   pci_name(asd_ha->pcidev));
			err = -ENOMEM;
			goto Err_unreq;
		}
	}

	return 0;
Err_unreq:
	pci_release_region(asd_ha->pcidev, i);
Err:
	if (i > 0) {
		io_handle = &asd_ha->io_handle[0];
		iounmap(io_handle->addr);
		pci_release_region(asd_ha->pcidev, 0);
	}
	return err;
}
