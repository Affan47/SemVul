qla4xxx_process_mbox_intr(struct scsi_qla_host *ha, int out_count)
{
	int intr_status;

	intr_status = readl(&ha->reg->ctrl_status);
	if (intr_status & INTR_PENDING) {


		ha->mbox_status_count = out_count;
		ha->isp_ops->interrupt_service_routine(ha, intr_status);
	}
}
