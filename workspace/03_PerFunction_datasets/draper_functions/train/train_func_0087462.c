flexcop_pci_exit(struct flexcop_pci *fc_pci)
{
	if (fc_pci->init_state & FC_PCI_INIT) {
		free_irq(fc_pci->pdev->irq, fc_pci);
		pci_iounmap(fc_pci->pdev, fc_pci->io_mem);
		pci_release_regions(fc_pci->pdev);
		pci_disable_device(fc_pci->pdev);
	}
	fc_pci->init_state &= ~FC_PCI_INIT;
}
