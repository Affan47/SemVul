pdc2026x_bmdma_start(struct ata_queued_cmd *qc)
{
	struct ata_port *ap = qc->ap;
	struct ata_device *adev = qc->dev;
	struct ata_taskfile *tf = &qc->tf;
	int sel66 = ap->port_no ? 0x08: 0x02;

	void __iomem *master = ap->host->ports[0]->ioaddr.bmdma_addr;
	void __iomem *clock = master + 0x11;
	void __iomem *atapi_reg = master + 0x20 + (4 * ap->port_no);

	u32 len;


	if (adev->dma_mode > XFER_UDMA_2)
		iowrite8(ioread8(clock) | sel66, clock);
	else
		iowrite8(ioread8(clock) & ~sel66, clock);


	pdc202xx_set_dmamode(ap, qc->dev);


	if ((tf->flags & ATA_TFLAG_LBA48) ||  tf->protocol == ATAPI_PROT_DMA) {
		len = qc->nbytes / 2;

		if (tf->flags & ATA_TFLAG_WRITE)
			len |= 0x06000000;
		else
			len |= 0x05000000;

		iowrite32(len, atapi_reg);
	}


	ata_bmdma_start(qc);
}
