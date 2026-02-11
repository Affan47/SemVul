bnx2x_iov_free_mem(struct bnx2x *bp)
{
	int i;

	if (!IS_SRIOV(bp))
		return;


	for (i = 0; i < BNX2X_VF_CIDS/ILT_PAGE_CIDS; i++) {
		struct hw_dma *cxt = &bp->vfdb->context[i];
		BNX2X_PCI_FREE(cxt->addr, cxt->mapping, cxt->size);
	}

	BNX2X_PCI_FREE(BP_VFDB(bp)->sp_dma.addr,
		       BP_VFDB(bp)->sp_dma.mapping,
		       BP_VFDB(bp)->sp_dma.size);

	BNX2X_PCI_FREE(BP_VF_MBX_DMA(bp)->addr,
		       BP_VF_MBX_DMA(bp)->mapping,
		       BP_VF_MBX_DMA(bp)->size);

	BNX2X_PCI_FREE(BP_VF_BULLETIN_DMA(bp)->addr,
		       BP_VF_BULLETIN_DMA(bp)->mapping,
		       BP_VF_BULLETIN_DMA(bp)->size);
}
