ccp_get_msix_irqs(struct ccp_device *ccp)
{
	struct ccp_pci *ccp_pci = ccp->dev_specific;
	struct device *dev = ccp->dev;
	struct pci_dev *pdev = container_of(dev, struct pci_dev, dev);
	struct msix_entry msix_entry[MSIX_VECTORS];
	unsigned int name_len = sizeof(ccp_pci->msix[0].name) - 1;
	int v, ret;

	for (v = 0; v < ARRAY_SIZE(msix_entry); v++)
		msix_entry[v].entry = v;

	ret = pci_enable_msix_range(pdev, msix_entry, 1, v);
	if (ret < 0)
		return ret;

	ccp_pci->msix_count = ret;
	for (v = 0; v < ccp_pci->msix_count; v++) {

		snprintf(ccp_pci->msix[v].name, name_len, "ccp-%u", v);
		ccp_pci->msix[v].vector = msix_entry[v].vector;
		ret = request_irq(ccp_pci->msix[v].vector, ccp_irq_handler,
				  0, ccp_pci->msix[v].name, dev);
		if (ret) {
			dev_notice(dev, "unable to allocate MSI-X IRQ (%d)\n",
				   ret);
			goto e_irq;
		}
	}

	return 0;

e_irq:
	while (v--)
		free_irq(ccp_pci->msix[v].vector, dev);

	pci_disable_msix(pdev);

	ccp_pci->msix_count = 0;

	return ret;
}
