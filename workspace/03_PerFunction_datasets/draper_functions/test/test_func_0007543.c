rhine_probe ( struct nic *nic, struct pci_device *pci ) {

    struct rhine_private *tp = (struct rhine_private *) nic->priv_data;

    if (!pci->ioaddr)
	return 0;

    rhine_probe1 (nic, pci, pci->ioaddr, pci->device, -1);

    adjust_pci_device ( pci );

    rhine_reset (nic);

    nic->nic_op	= &rhine_operations;

    nic->irqno	  = pci->irq;
    nic->ioaddr   = tp->ioaddr;

    return 1;
}
