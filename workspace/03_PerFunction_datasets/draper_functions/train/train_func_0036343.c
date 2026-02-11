do_pata_set_dmamode(struct ata_port *ap, struct ata_device *adev, int isich)
{
	struct pci_dev *dev	= to_pci_dev(ap->host->dev);
	unsigned long flags;
	u8 speed		= adev->dma_mode;
	int devid		= adev->devno + 2 * ap->port_no;
	u8 udma_enable		= 0;

	if (speed >= XFER_UDMA_0) {
		unsigned int udma = speed - XFER_UDMA_0;
		u16 udma_timing;
		u16 ideconf;
		int u_clock, u_speed;

		spin_lock_irqsave(&piix_lock, flags);

		pci_read_config_byte(dev, 0x48, &udma_enable);


		u_speed = min(2 - (udma & 1), udma);
		if (udma == 5)
			u_clock = 0x1000;
		else if (udma > 2)
			u_clock = 1;
		else
			u_clock = 0;

		udma_enable |= (1 << devid);


		pci_read_config_word(dev, 0x4A, &udma_timing);
		udma_timing &= ~(3 << (4 * devid));
		udma_timing |= u_speed << (4 * devid);
		pci_write_config_word(dev, 0x4A, udma_timing);

		if (isich) {

			pci_read_config_word(dev, 0x54, &ideconf);
			ideconf &= ~(0x1001 << devid);
			ideconf |= u_clock << devid;


			pci_write_config_word(dev, 0x54, ideconf);
		}

		pci_write_config_byte(dev, 0x48, udma_enable);

		spin_unlock_irqrestore(&piix_lock, flags);
	} else {

		unsigned int mwdma = speed - XFER_MW_DMA_0;
		const unsigned int needed_pio[3] = {
			XFER_PIO_0, XFER_PIO_3, XFER_PIO_4
		};
		int pio = needed_pio[mwdma] - XFER_PIO_0;


		piix_set_timings(ap, adev, pio);
	}
}
