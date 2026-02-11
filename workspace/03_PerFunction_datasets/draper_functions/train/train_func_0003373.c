edac_pci_do_parity_check(void)
{
	int before_count;

	edac_dbg(3, "\n");


	if (!check_pci_errors)
		return;

	before_count = atomic_read(&pci_parity_count);


	edac_pci_dev_parity_iterator(edac_pci_dev_parity_test);


	if (edac_pci_get_panic_on_pe()) {

		if (before_count != atomic_read(&pci_parity_count))
			panic("EDAC: PCI Parity Error");
	}
}
