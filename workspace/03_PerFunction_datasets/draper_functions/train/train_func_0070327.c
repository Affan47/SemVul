sync_dma(unsigned int i, struct hostdata *ha)
{
	unsigned int pci_dir;
	struct mscp *cpp;
	struct scsi_cmnd *SCpnt;

	cpp = &ha->cp[i];
	SCpnt = cpp->SCpnt;
	pci_dir = SCpnt->sc_data_direction;

	if (DEV2H(cpp->sense_addr))
		pci_dma_sync_single_for_cpu(ha->pdev, DEV2H(cpp->sense_addr),
					    DEV2H(cpp->sense_len),
					    PCI_DMA_FROMDEVICE);

	if (scsi_sg_count(SCpnt))
		pci_dma_sync_sg_for_cpu(ha->pdev, scsi_sglist(SCpnt),
					scsi_sg_count(SCpnt), pci_dir);

	if (!DEV2H(cpp->data_len))
		pci_dir = PCI_DMA_BIDIRECTIONAL;

	if (DEV2H(cpp->data_address))
		pci_dma_sync_single_for_cpu(ha->pdev,
					    DEV2H(cpp->data_address),
					    DEV2H(cpp->data_len), pci_dir);
}
