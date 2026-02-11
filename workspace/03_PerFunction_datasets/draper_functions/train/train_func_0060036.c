velocity_probe( struct nic *nic, struct pci_device *pci)
{
	int ret, i;
	struct mac_regs *regs;

	printf("via-velocity.c: Found %s Vendor=0x%hX Device=0x%hX\n",
	       pci->driver_name, pci->vendor, pci->device);


	vptr = &vptx;
	info = chip_info_table;

	velocity_init_info(pci, vptr, info);


	ret = velocity_get_pci_info(vptr, pci);
	if (ret < 0) {
		printf("Failed to find PCI device.\n");
		return 0;
	}

	regs = ioremap(vptr->memaddr, vptr->io_size);
	if (regs == NULL) {
		printf("Unable to remap io\n");
		return 0;
	}

	vptr->mac_regs = regs;

	BASE = vptr->ioaddr;

	printf("Chip ID: %hX\n", vptr->chip_id);

	for (i = 0; i < 6; i++)
		nic->node_addr[i] = readb(&regs->PAR[i]);

	DBG ( "%s: %s at ioaddr %#hX\n", pci->driver_name, eth_ntoa ( nic->node_addr ),
	      (unsigned int) BASE );

	velocity_get_options(&vptr->options, 0, pci->driver_name);


	vptr->options.flags &= 0x00FFFFFFUL;


	vptr->flags =
	    vptr->options.
	    flags | (0x00FFFFFFUL   & 0xFF000000UL);

	vptr->wol_opts = vptr->options.wol_opts;
	vptr->flags |= VELOCITY_FLAGS_WOL_ENABLED;

	vptr->phy_id = MII_GET_PHY_ID(vptr->mac_regs);

	if (vptr->flags & VELOCITY_FLAGS_TX_CSUM) {
		printf("features missing\n");
	}


	check_connection_type(vptr->mac_regs);
	velocity_open(nic, pci);


	nic->nic_op = &velocity_operations;
	return 1;
}
