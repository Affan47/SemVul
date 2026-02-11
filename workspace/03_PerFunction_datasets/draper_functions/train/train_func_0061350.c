pdc_ata_init_one(struct pci_dev *pdev,
			    const struct pci_device_id *ent)
{
	const struct ata_port_info *pi = &pdc_port_info[ent->driver_data];
	const struct ata_port_info *ppi[PDC_MAX_PORTS];
	struct ata_host *host;
	struct pdc_host_priv *hpriv;
	void __iomem *host_mmio;
	int n_ports, i, rc;
	int is_sataii_tx4;

	ata_print_version_once(&pdev->dev, DRV_VERSION);


	rc = pcim_enable_device(pdev);
	if (rc)
		return rc;

	rc = pcim_iomap_regions(pdev, 1 << PDC_MMIO_BAR, DRV_NAME);
	if (rc == -EBUSY)
		pcim_pin_device(pdev);
	if (rc)
		return rc;
	host_mmio = pcim_iomap_table(pdev)[PDC_MMIO_BAR];


	n_ports = 2;
	if (pi->flags & PDC_FLAG_4_PORTS)
		n_ports = 4;
	for (i = 0; i < n_ports; i++)
		ppi[i] = pi;

	if (pi->flags & PDC_FLAG_SATA_PATA) {
		u8 tmp = readb(host_mmio + PDC_FLASH_CTL + 1);
		if (!(tmp & 0x80))
			ppi[n_ports++] = pi + 1;
	}

	host = ata_host_alloc_pinfo(&pdev->dev, ppi, n_ports);
	if (!host) {
		dev_err(&pdev->dev, "failed to allocate host\n");
		return -ENOMEM;
	}
	hpriv = devm_kzalloc(&pdev->dev, sizeof *hpriv, GFP_KERNEL);
	if (!hpriv)
		return -ENOMEM;
	spin_lock_init(&hpriv->hard_reset_lock);
	host->private_data = hpriv;
	host->iomap = pcim_iomap_table(pdev);

	is_sataii_tx4 = pdc_is_sataii_tx4(pi->flags);
	for (i = 0; i < host->n_ports; i++) {
		struct ata_port *ap = host->ports[i];
		unsigned int ata_no = pdc_port_no_to_ata_no(i, is_sataii_tx4);
		unsigned int ata_offset = 0x200 + ata_no * 0x80;
		unsigned int scr_offset = 0x400 + ata_no * 0x100;

		pdc_ata_setup_port(ap, host_mmio + ata_offset, host_mmio + scr_offset);

		ata_port_pbar_desc(ap, PDC_MMIO_BAR, -1, "mmio");
		ata_port_pbar_desc(ap, PDC_MMIO_BAR, ata_offset, "ata");
	}


	pdc_host_init(host);

	rc = dma_set_mask(&pdev->dev, ATA_DMA_MASK);
	if (rc)
		return rc;
	rc = dma_set_coherent_mask(&pdev->dev, ATA_DMA_MASK);
	if (rc)
		return rc;


	pci_set_master(pdev);
	return ata_host_activate(host, pdev->irq, pdc_interrupt, IRQF_SHARED,
				 &pdc_ata_sht);
}
