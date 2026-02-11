mega_build_sglist(adapter_t *adapter, scb_t *scb, u32 *buf, u32 *len)
{
	struct scatterlist *sg;
	Scsi_Cmnd	*cmd;
	int	sgcnt;
	int	idx;

	cmd = scb->cmd;


	sgcnt = scsi_dma_map(cmd);

	scb->dma_type = MEGA_SGLIST;

	BUG_ON(sgcnt > adapter->sglen || sgcnt < 0);

	*len = 0;

	if (scsi_sg_count(cmd) == 1 && !adapter->has_64bit_addr) {
		sg = scsi_sglist(cmd);
		scb->dma_h_bulkdata = sg_dma_address(sg);
		*buf = (u32)scb->dma_h_bulkdata;
		*len = sg_dma_len(sg);
		return 0;
	}

	scsi_for_each_sg(cmd, sg, sgcnt, idx) {
		if (adapter->has_64bit_addr) {
			scb->sgl64[idx].address = sg_dma_address(sg);
			*len += scb->sgl64[idx].length = sg_dma_len(sg);
		} else {
			scb->sgl[idx].address = sg_dma_address(sg);
			*len += scb->sgl[idx].length = sg_dma_len(sg);
		}
	}


	*buf = scb->sgl_dma_addr;


	return sgcnt;
}
