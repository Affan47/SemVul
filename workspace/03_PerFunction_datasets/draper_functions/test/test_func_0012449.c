pdc20621_qc_prep(struct ata_queued_cmd *qc)
{
	switch (qc->tf.protocol) {
	case ATA_PROT_DMA:
		pdc20621_dma_prep(qc);
		break;
	case ATA_PROT_NODATA:
		pdc20621_nodata_prep(qc);
		break;
	default:
		break;
	}
}
