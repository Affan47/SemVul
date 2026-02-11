inic_fill_sg(struct inic_prd *prd, struct ata_queued_cmd *qc)
{
	struct scatterlist *sg;
	unsigned int si;
	u8 flags = 0;

	if (qc->tf.flags & ATA_TFLAG_WRITE)
		flags |= PRD_WRITE;

	if (ata_is_dma(qc->tf.protocol))
		flags |= PRD_DMA;

	for_each_sg(qc->sg, sg, qc->n_elem, si) {
		prd->mad = cpu_to_le32(sg_dma_address(sg));
		prd->len = cpu_to_le16(sg_dma_len(sg));
		prd->flags = flags;
		prd++;
	}

	WARN_ON(!si);
	prd[-1].flags |= PRD_END;
}
