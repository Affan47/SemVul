asd_extend_cmdctx(struct asd_ha_struct *asd_ha)
{
	dma_addr_t dma_handle;
	unsigned long dma_addr;
	u32 d;
	int size;

	asd_ha->hw_prof.scb_ext = NULL;
	if (max_cmnds <= asd_ha->hw_prof.max_scbs || max_cmnds > 0xFFFF) {
		max_cmnds = asd_ha->hw_prof.max_scbs;
		return 0;
	}

	size = (max_cmnds - asd_ha->hw_prof.max_scbs + 1) * ASD_SCB_SIZE;

	asd_ha->hw_prof.scb_ext = asd_alloc_coherent(asd_ha, size, GFP_KERNEL);
	if (!asd_ha->hw_prof.scb_ext) {
		asd_printk("couldn't allocate memory for %d commands\n",
			   max_cmnds);
		max_cmnds = asd_ha->hw_prof.max_scbs;
		return -ENOMEM;
	}
	dma_handle = asd_ha->hw_prof.scb_ext->dma_handle;
	dma_addr = ALIGN((unsigned long) dma_handle, ASD_SCB_SIZE);
	dma_addr -= asd_ha->hw_prof.max_scbs * ASD_SCB_SIZE;
	dma_handle = (dma_addr_t) dma_addr;
	asd_write_reg_addr(asd_ha, CMDCTXBASE, dma_handle);
	d = asd_read_reg_dword(asd_ha, CTXDOMAIN);
	d &= ~1;
	asd_write_reg_dword(asd_ha, CTXDOMAIN, d);

	asd_ha->hw_prof.max_scbs = max_cmnds;

	return 0;
}
