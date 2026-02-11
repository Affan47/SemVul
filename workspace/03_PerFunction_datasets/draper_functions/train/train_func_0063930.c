qla2x00_build_scsi_iocbs_64(srb_t *sp, cmd_entry_t *cmd_pkt,
    uint16_t tot_dsds)
{
	uint16_t	avail_dsds;
	uint32_t	*cur_dsd;
	scsi_qla_host_t	*vha;
	struct scsi_cmnd *cmd;
	struct scatterlist *sg;
	int i;

	cmd = GET_CMD_SP(sp);


	*((uint32_t *)(&cmd_pkt->entry_type)) = cpu_to_le32(COMMAND_A64_TYPE);


	if (!scsi_bufflen(cmd) || cmd->sc_data_direction == DMA_NONE) {
		cmd_pkt->byte_count = cpu_to_le32(0);
		return;
	}

	vha = sp->fcport->vha;
	cmd_pkt->control_flags |= cpu_to_le16(qla2x00_get_cmd_direction(sp));


	avail_dsds = 2;
	cur_dsd = (uint32_t *)&cmd_pkt->dseg_0_address;


	scsi_for_each_sg(cmd, sg, tot_dsds, i) {
		dma_addr_t	sle_dma;
		cont_a64_entry_t *cont_pkt;


		if (avail_dsds == 0) {


			cont_pkt = qla2x00_prep_cont_type1_iocb(vha, vha->req);
			cur_dsd = (uint32_t *)cont_pkt->dseg_0_address;
			avail_dsds = 5;
		}

		sle_dma = sg_dma_address(sg);
		*cur_dsd++ = cpu_to_le32(LSD(sle_dma));
		*cur_dsd++ = cpu_to_le32(MSD(sle_dma));
		*cur_dsd++ = cpu_to_le32(sg_dma_len(sg));
		avail_dsds--;
	}
}
