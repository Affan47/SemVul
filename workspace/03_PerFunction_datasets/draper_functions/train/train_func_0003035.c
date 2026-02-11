nv_adma_slave_config(struct scsi_device *sdev)
{
	struct ata_port *ap = ata_shost_to_port(sdev->host);
	struct nv_adma_port_priv *pp = ap->private_data;
	struct nv_adma_port_priv *port0, *port1;
	struct scsi_device *sdev0, *sdev1;
	struct pci_dev *pdev = to_pci_dev(ap->host->dev);
	unsigned long segment_boundary, flags;
	unsigned short sg_tablesize;
	int rc;
	int adma_enable;
	u32 current_reg, new_reg, config_mask;

	rc = ata_scsi_slave_config(sdev);

	if (sdev->id >= ATA_MAX_DEVICES || sdev->channel || sdev->lun)

		return rc;

	spin_lock_irqsave(ap->lock, flags);

	if (ap->link.device[sdev->id].class == ATA_DEV_ATAPI) {


		segment_boundary = ATA_DMA_BOUNDARY;


		sg_tablesize = LIBATA_MAX_PRD - 1;


		adma_enable = 0;
		nv_adma_register_mode(ap);
	} else {
		segment_boundary = NV_ADMA_DMA_BOUNDARY;
		sg_tablesize = NV_ADMA_SGTBL_TOTAL_LEN;
		adma_enable = 1;
	}

	pci_read_config_dword(pdev, NV_MCP_SATA_CFG_20, &current_reg);

	if (ap->port_no == 1)
		config_mask = NV_MCP_SATA_CFG_20_PORT1_EN |
			      NV_MCP_SATA_CFG_20_PORT1_PWB_EN;
	else
		config_mask = NV_MCP_SATA_CFG_20_PORT0_EN |
			      NV_MCP_SATA_CFG_20_PORT0_PWB_EN;

	if (adma_enable) {
		new_reg = current_reg | config_mask;
		pp->flags &= ~NV_ADMA_ATAPI_SETUP_COMPLETE;
	} else {
		new_reg = current_reg & ~config_mask;
		pp->flags |= NV_ADMA_ATAPI_SETUP_COMPLETE;
	}

	if (current_reg != new_reg)
		pci_write_config_dword(pdev, NV_MCP_SATA_CFG_20, new_reg);

	port0 = ap->host->ports[0]->private_data;
	port1 = ap->host->ports[1]->private_data;
	sdev0 = ap->host->ports[0]->link.device[0].sdev;
	sdev1 = ap->host->ports[1]->link.device[0].sdev;
	if ((port0->flags & NV_ADMA_ATAPI_SETUP_COMPLETE) ||
	    (port1->flags & NV_ADMA_ATAPI_SETUP_COMPLETE)) {


		if (sdev0)
			blk_queue_bounce_limit(sdev0->request_queue,
					       ATA_DMA_MASK);
		if (sdev1)
			blk_queue_bounce_limit(sdev1->request_queue,
					       ATA_DMA_MASK);

		dma_set_mask(&pdev->dev, ATA_DMA_MASK);
	} else {

		dma_set_mask(&pdev->dev, pp->adma_dma_mask);
		if (sdev0)
			blk_queue_bounce_limit(sdev0->request_queue,
					       pp->adma_dma_mask);
		if (sdev1)
			blk_queue_bounce_limit(sdev1->request_queue,
					       pp->adma_dma_mask);
	}

	blk_queue_segment_boundary(sdev->request_queue, segment_boundary);
	blk_queue_max_segments(sdev->request_queue, sg_tablesize);
	ata_port_info(ap,
		      "DMA mask 0x%llX, segment boundary 0x%lX, hw segs %hu\n",
		      (unsigned long long)*ap->host->dev->dma_mask,
		      segment_boundary, sg_tablesize);

	spin_unlock_irqrestore(ap->lock, flags);

	return rc;
}
