generic_set_mode(struct ata_link *link, struct ata_device **unused)
{
	struct ata_port *ap = link->ap;
	const struct pci_device_id *id = ap->host->private_data;
	int dma_enabled = 0;
	struct ata_device *dev;

	if (id->driver_data & ATA_GEN_FORCE_DMA) {
		dma_enabled = 0xff;
	} else if (ap->ioaddr.bmdma_addr) {

		dma_enabled = ioread8(ap->ioaddr.bmdma_addr + ATA_DMA_STATUS);
	}

	ata_for_each_dev(dev, link, ENABLED) {

		dev->pio_mode = XFER_PIO_0;
		dev->dma_mode = XFER_MW_DMA_0;


		if (dma_enabled & (1 << (5 + dev->devno))) {
			unsigned int xfer_mask = ata_id_xfermask(dev->id);
			const char *name;

			if (xfer_mask & (ATA_MASK_MWDMA | ATA_MASK_UDMA))
				name = ata_mode_string(xfer_mask);
			else {

				name = "DMA";
				xfer_mask |= ata_xfer_mode2mask(XFER_MW_DMA_0);
			}

			ata_dev_info(dev, "configured for %s\n", name);

			dev->xfer_mode = ata_xfer_mask2mode(xfer_mask);
			dev->xfer_shift = ata_xfer_mode2shift(dev->xfer_mode);
			dev->flags &= ~ATA_DFLAG_PIO;
		} else {
			ata_dev_info(dev, "configured for PIO\n");
			dev->xfer_mode = XFER_PIO_0;
			dev->xfer_shift = ATA_SHIFT_PIO;
			dev->flags |= ATA_DFLAG_PIO;
		}
	}
	return 0;
}
