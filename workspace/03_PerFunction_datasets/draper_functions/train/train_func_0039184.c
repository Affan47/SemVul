qla4xxx_task_work(struct work_struct *wdata)
{
	struct ql4_task_data *task_data;
	struct scsi_qla_host *ha;
	struct passthru_status *sts;
	struct iscsi_task *task;
	struct iscsi_hdr *hdr;
	uint8_t *data;
	uint32_t data_len;
	struct iscsi_conn *conn;
	int hdr_len;
	itt_t itt;

	task_data = container_of(wdata, struct ql4_task_data, task_work);
	ha = task_data->ha;
	task = task_data->task;
	sts = &task_data->sts;
	hdr_len = sizeof(struct iscsi_hdr);

	DEBUG3(printk(KERN_INFO "Status returned\n"));
	DEBUG3(qla4xxx_dump_buffer(sts, 64));
	DEBUG3(printk(KERN_INFO "Response buffer"));
	DEBUG3(qla4xxx_dump_buffer(task_data->resp_buffer, 64));

	conn = task->conn;

	switch (sts->completionStatus) {
	case PASSTHRU_STATUS_COMPLETE:
		hdr = (struct iscsi_hdr *)task_data->resp_buffer;

		itt = sts->handle;
		hdr->itt = itt;
		data = task_data->resp_buffer + hdr_len;
		data_len = task_data->resp_len - hdr_len;
		iscsi_complete_pdu(conn, hdr, data, data_len);
		break;
	default:
		ql4_printk(KERN_ERR, ha, "Passthru failed status = 0x%x\n",
			   sts->completionStatus);
		break;
	}
	return;
}
