bnx2i_map_scsi_sg(struct bnx2i_hba *hba, struct bnx2i_cmd *cmd)
{
	struct scsi_cmnd *sc = cmd->scsi_cmd;
	struct iscsi_bd *bd = cmd->io_tbl.bd_tbl;
	struct scatterlist *sg;
	int byte_count = 0;
	int bd_count = 0;
	int sg_count;
	int sg_len;
	u64 addr;
	int i;

	BUG_ON(scsi_sg_count(sc) > ISCSI_MAX_BDS_PER_CMD);

	sg_count = scsi_dma_map(sc);

	scsi_for_each_sg(sc, sg, sg_count, i) {
		sg_len = sg_dma_len(sg);
		addr = (u64) sg_dma_address(sg);
		bd[bd_count].buffer_addr_lo = addr & 0xffffffff;
		bd[bd_count].buffer_addr_hi = addr >> 32;
		bd[bd_count].buffer_length = sg_len;
		bd[bd_count].flags = 0;
		if (bd_count == 0)
			bd[bd_count].flags = ISCSI_BD_FIRST_IN_BD_CHAIN;

		byte_count += sg_len;
		bd_count++;
	}

	if (bd_count)
		bd[bd_count - 1].flags |= ISCSI_BD_LAST_IN_BD_CHAIN;

	BUG_ON(byte_count != scsi_bufflen(sc));
	return bd_count;
}
