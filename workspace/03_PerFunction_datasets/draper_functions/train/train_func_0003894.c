ata_scsi_write_same_xlat(struct ata_queued_cmd *qc)
{
	struct ata_taskfile *tf = &qc->tf;
	struct scsi_cmnd *scmd = qc->scsicmd;
	struct ata_device *dev = qc->dev;
	const u8 *cdb = scmd->cmnd;
	u64 block;
	u32 n_block;
	u32 size;
	void *buf;


	if (unlikely(!dev->dma_mode))
		goto invalid_fld;

	if (unlikely(scmd->cmd_len < 16))
		goto invalid_fld;
	scsi_16_lba_len(cdb, &block, &n_block);


	if (unlikely(!(cdb[1] & 0x8)))
		goto invalid_fld;


	if (!scsi_sg_count(scmd))
		goto invalid_fld;

	buf = page_address(sg_page(scsi_sglist(scmd)));
	size = ata_set_lba_range_entries(buf, 512, block, n_block);

	if (ata_ncq_enabled(dev) && ata_fpdma_dsm_supported(dev)) {

		tf->protocol = ATA_PROT_NCQ;
		tf->command = ATA_CMD_FPDMA_SEND;
		tf->hob_nsect = ATA_SUBCMD_FPDMA_SEND_DSM & 0x1f;
		tf->nsect = qc->tag << 3;
		tf->hob_feature = (size / 512) >> 8;
		tf->feature = size / 512;

		tf->auxiliary = 1;
	} else {
		tf->protocol = ATA_PROT_DMA;
		tf->hob_feature = 0;
		tf->feature = ATA_DSM_TRIM;
		tf->hob_nsect = (size / 512) >> 8;
		tf->nsect = size / 512;
		tf->command = ATA_CMD_DSM;
	}

	tf->flags |= ATA_TFLAG_ISADDR | ATA_TFLAG_DEVICE | ATA_TFLAG_LBA48 |
		     ATA_TFLAG_WRITE;

	ata_qc_set_pc_nbytes(qc);

	return 0;

 invalid_fld:
	ata_scsi_set_sense(scmd, ILLEGAL_REQUEST, 0x24, 0x00);

	return 1;
}
