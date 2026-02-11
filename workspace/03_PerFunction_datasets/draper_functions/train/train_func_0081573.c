cs5530_set_dmamode(struct ata_port *ap, struct ata_device *adev)
{
	void __iomem *base = cs5530_port_base(ap);
	u32 tuning, timing = 0;
	u8 reg;


	tuning = ioread32(base + 0x04);

	switch(adev->dma_mode) {
		case XFER_UDMA_0:
			timing  = 0x00921250;break;
		case XFER_UDMA_1:
			timing  = 0x00911140;break;
		case XFER_UDMA_2:
			timing  = 0x00911030;break;
		case XFER_MW_DMA_0:
			timing  = 0x00077771;break;
		case XFER_MW_DMA_1:
			timing  = 0x00012121;break;
		case XFER_MW_DMA_2:
			timing  = 0x00002020;break;
		default:
			BUG();
	}

	timing |= (tuning & 0x80000000UL);
	if (adev->devno == 0)
		iowrite32(timing, base + 0x04);
	else {
		if (timing & 0x00100000)
			tuning |= 0x00100000;
		else
			tuning &= ~0x00100000;
		iowrite32(tuning, base + 0x04);
		iowrite32(timing, base + 0x0C);
	}


	reg = ioread8(ap->ioaddr.bmdma_addr + ATA_DMA_STATUS);
	reg |= (1 << (5 + adev->devno));
	iowrite8(reg, ap->ioaddr.bmdma_addr + ATA_DMA_STATUS);


	ap->private_data = adev;
}
