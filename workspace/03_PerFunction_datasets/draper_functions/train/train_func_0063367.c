pcnet32_setup_if_duplex ( struct pcnet32_private *priv )
{
	unsigned long ioaddr = priv->pci_dev->ioaddr;
	u16 val;


	val = priv->a->read_bcr ( ioaddr, 2 ) & ~2;
	if ( priv->options & PCNET32_PORT_ASEL )
		val |= 2;
	priv->a->write_bcr ( ioaddr, 2, val );


	if ( priv->full_duplex ) {
		val = priv->a->read_bcr ( ioaddr, 9 ) & ~3;
		if ( priv->options & PCNET32_PORT_FD ) {
			val |= 1;
			if ( priv->options == ( PCNET32_PORT_FD | PCNET32_PORT_AUI ) )
				val |= 2;
		} else if ( priv->options & PCNET32_PORT_ASEL ) {

			if ( priv->chip_version == 0x2627 )
				val |= 3;
		}
		priv->a->write_bcr ( ioaddr, 9, val );
	}


	val = priv->a->read_csr ( ioaddr, 124 ) & ~0x10;
	if ( ( priv->options & PCNET32_PORT_PORTSEL ) == PCNET32_PORT_GPSI )
		val |= 0x10;
	priv->a->write_bcr ( ioaddr, 124, val );


	u16 subsys_vend_id, subsys_dev_id;
	pci_read_config_word ( priv->pci_dev,
			       PCI_SUBSYSTEM_VENDOR_ID,
			       &subsys_vend_id );
	pci_read_config_word ( priv->pci_dev,
			       PCI_SUBSYSTEM_ID,
			       &subsys_dev_id );
	if ( subsys_vend_id == PCI_VENDOR_ID_AT &&
	     ( ( subsys_dev_id == PCI_SUBDEVICE_ID_AT_2700FX ) ||
	       ( subsys_dev_id == PCI_SUBDEVICE_ID_AT_2701FX ) ) ) {
		priv->options = PCNET32_PORT_FD | PCNET32_PORT_100;
	}

	if ( priv->mii && ! ( priv->options & PCNET32_PORT_ASEL ) ) {

		val = priv->a->read_bcr ( ioaddr, 32 ) & ~0x38;
		if ( priv->options & PCNET32_PORT_FD )
			val |= 0x10;
		if ( priv->options & PCNET32_PORT_100 )
			val |= 0x08;
		priv->a->write_bcr ( ioaddr, 32, val );
	} else if ( priv->options & PCNET32_PORT_ASEL ) {

		if ( ( priv->chip_version != 0x2420 ) &&
		     ( priv->chip_version != 0x2621 ) ) {

			val = priv->a->read_bcr ( ioaddr, 32 ) & ~0x98;
			val |= 0x20;
			priv->a->write_bcr ( ioaddr, 32, val );
		}
	}
}
