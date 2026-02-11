ipr_reinit_ipr_cmnd(struct ipr_cmnd *ipr_cmd)
{
	struct ipr_ioarcb *ioarcb = &ipr_cmd->ioarcb;
	struct ipr_ioasa *ioasa = &ipr_cmd->s.ioasa;
	struct ipr_ioasa64 *ioasa64 = &ipr_cmd->s.ioasa64;
	dma_addr_t dma_addr = ipr_cmd->dma_addr;
	int hrrq_id;

	hrrq_id = ioarcb->cmd_pkt.hrrq_id;
	memset(&ioarcb->cmd_pkt, 0, sizeof(struct ipr_cmd_pkt));
	ioarcb->cmd_pkt.hrrq_id = hrrq_id;
	ioarcb->data_transfer_length = 0;
	ioarcb->read_data_transfer_length = 0;
	ioarcb->ioadl_len = 0;
	ioarcb->read_ioadl_len = 0;

	if (ipr_cmd->ioa_cfg->sis64) {
		ioarcb->u.sis64_addr_data.data_ioadl_addr =
			cpu_to_be64(dma_addr + offsetof(struct ipr_cmnd, i.ioadl64));
		ioasa64->u.gata.status = 0;
	} else {
		ioarcb->write_ioadl_addr =
			cpu_to_be32(dma_addr + offsetof(struct ipr_cmnd, i.ioadl));
		ioarcb->read_ioadl_addr = ioarcb->write_ioadl_addr;
		ioasa->u.gata.status = 0;
	}

	ioasa->hdr.ioasc = 0;
	ioasa->hdr.residual_data_len = 0;
	ipr_cmd->scsi_cmd = NULL;
	ipr_cmd->qc = NULL;
	ipr_cmd->sense_buffer[0] = 0;
	ipr_cmd->dma_use_sg = 0;
}
