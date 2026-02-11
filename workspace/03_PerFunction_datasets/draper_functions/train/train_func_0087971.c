mpiix_pre_reset(struct ata_link *link, unsigned long deadline)
{
	struct ata_port *ap = link->ap;
	struct pci_dev *pdev = to_pci_dev(ap->host->dev);
	static const struct pci_bits mpiix_enable_bits = { 0x6D, 1, 0x80, 0x80 };

	if (!pci_test_config_bits(pdev, &mpiix_enable_bits))
		return -ENOENT;

	return ata_sff_prereset(link, deadline);
}
