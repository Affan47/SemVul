eata2x_release(struct Scsi_Host *shost)
{
	struct hostdata *ha = (struct hostdata *)shost->hostdata;
	unsigned int i;

	for (i = 0; i < shost->can_queue; i++)
		kfree((&ha->cp[i])->sglist);

	for (i = 0; i < shost->can_queue; i++)
		pci_unmap_single(ha->pdev, ha->cp[i].cp_dma_addr,
				 sizeof(struct mscp), PCI_DMA_BIDIRECTIONAL);

	if (ha->sp_cpu_addr)
		pci_free_consistent(ha->pdev, sizeof(struct mssp),
				    ha->sp_cpu_addr, ha->sp_dma_addr);

	free_irq(shost->irq, &sha[ha->board_number]);

	if (shost->dma_channel != NO_DMA)
		free_dma(shost->dma_channel);

	release_region(shost->io_port, shost->n_io_port);
	scsi_unregister(shost);
	return 0;
}
