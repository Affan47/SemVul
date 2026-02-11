pci_msi_setup_msi_irqs(struct pci_dev *dev, int nvec, int type)
{
	struct irq_domain *domain;

	domain = pci_msi_get_domain(dev);
	if (domain && irq_domain_is_hierarchy(domain))
		return pci_msi_domain_alloc_irqs(domain, dev, nvec, type);

	return arch_setup_msi_irqs(dev, nvec, type);
}
