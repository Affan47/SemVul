blogic_create_addlccbs(struct blogic_adapter *adapter,
					int addl_ccbs, bool print_success)
{
	int blk_size = BLOGIC_CCB_GRP_ALLOCSIZE * sizeof(struct blogic_ccb);
	int prev_alloc = adapter->alloc_ccbs;
	void *blk_pointer;
	dma_addr_t blkp;
	if (addl_ccbs <= 0)
		return;
	while (adapter->alloc_ccbs - prev_alloc < addl_ccbs) {
		blk_pointer = pci_alloc_consistent(adapter->pci_device,
							blk_size, &blkp);
		if (blk_pointer == NULL)
			break;
		blogic_init_ccbs(adapter, blk_pointer, blk_size, blkp);
	}
	if (adapter->alloc_ccbs > prev_alloc) {
		if (print_success)
			blogic_notice("Allocated %d additional CCBs (total now %d)\n", adapter, adapter->alloc_ccbs - prev_alloc, adapter->alloc_ccbs);
		return;
	}
	blogic_notice("Failed to allocate additional CCBs\n", adapter);
	if (adapter->drvr_qdepth > adapter->alloc_ccbs - adapter->tgt_count) {
		adapter->drvr_qdepth = adapter->alloc_ccbs - adapter->tgt_count;
		adapter->scsi_host->can_queue = adapter->drvr_qdepth;
	}
}
