adjust_pci_device ( struct pci_device *pci ) {
	unsigned short new_command, pci_command;
	unsigned char pci_latency;

	pci_read_config_word ( pci, PCI_COMMAND, &pci_command );
	new_command = ( pci_command | PCI_COMMAND_MASTER |
			PCI_COMMAND_MEM | PCI_COMMAND_IO );
	if ( pci_command != new_command ) {
		DBG ( "PCI BIOS has not enabled device %02x:%02x.%x! "
		      "Updating PCI command %04x->%04x\n", pci->bus,
		      PCI_SLOT ( pci->devfn ), PCI_FUNC ( pci->devfn ),
		      pci_command, new_command );
		pci_write_config_word ( pci, PCI_COMMAND, new_command );
	}

	pci_read_config_byte ( pci, PCI_LATENCY_TIMER, &pci_latency);
	if ( pci_latency < 32 ) {
		DBG ( "PCI device %02x:%02x.%x latency timer is unreasonably "
		      "low at %d. Setting to 32.\n", pci->bus,
		      PCI_SLOT ( pci->devfn ), PCI_FUNC ( pci->devfn ),
		      pci_latency );
		pci_write_config_byte ( pci, PCI_LATENCY_TIMER, 32);
	}
}
