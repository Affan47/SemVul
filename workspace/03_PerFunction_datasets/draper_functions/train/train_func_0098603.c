forcedeth_map_regs ( struct forcedeth_private *priv )
{
	void *ioaddr;
	uint32_t bar;
	unsigned long addr;
	u32 register_size;
	int reg;
	int rc;


	if ( priv->driver_data & ( DEV_HAS_VLAN | DEV_HAS_MSI_X |
		DEV_HAS_POWER_CNTRL | DEV_HAS_STATISTICS_V2 |
		DEV_HAS_STATISTICS_V3 ) ) {
		register_size = NV_PCI_REGSZ_VER3;
	} else if ( priv->driver_data & DEV_HAS_STATISTICS_V1 ) {
		register_size = NV_PCI_REGSZ_VER2;
	} else {
		register_size = NV_PCI_REGSZ_VER1;
	}


	rc = -EINVAL;
	addr = 0;
	for ( reg = PCI_BASE_ADDRESS_0; reg <= PCI_BASE_ADDRESS_5; reg += 4 ) {
		pci_read_config_dword ( priv->pci_dev, reg, &bar );

		if ( ( ( bar & PCI_BASE_ADDRESS_SPACE ) ==
			 PCI_BASE_ADDRESS_SPACE_MEMORY ) &&
		       ( pci_bar_size ( priv->pci_dev, reg ) >=
			 register_size ) ) {
			addr = pci_bar_start ( priv->pci_dev, reg );
			break;
		}
	}

	if ( reg > PCI_BASE_ADDRESS_5 ) {
		DBG ( "Couldn't find register window\n" );
		goto err_bar_sz;
	}

	rc = -ENOMEM;
	ioaddr = ioremap ( addr, register_size );
	if ( ! ioaddr ) {
		DBG ( "Cannot remap MMIO\n" );
		goto err_ioremap;
	}

	priv->mmio_addr = ioaddr;

	return 0;

err_bar_sz:
err_ioremap:
	return rc;
}
