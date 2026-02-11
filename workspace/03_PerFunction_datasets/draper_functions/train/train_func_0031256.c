qla1280_error_entry(struct scsi_qla_host *ha, struct response *pkt,
		    struct list_head *done_q)
{
	struct srb *sp;
	uint32_t handle = le32_to_cpu(pkt->handle);

	ENTER("qla1280_error_entry");

	if (pkt->entry_status & BIT_3)
		dprintk(2, "qla1280_error_entry: BAD PAYLOAD flag error\n");
	else if (pkt->entry_status & BIT_2)
		dprintk(2, "qla1280_error_entry: BAD HEADER flag error\n");
	else if (pkt->entry_status & BIT_1)
		dprintk(2, "qla1280_error_entry: FULL flag error\n");
	else
		dprintk(2, "qla1280_error_entry: UNKNOWN flag error\n");


	if (handle < MAX_OUTSTANDING_COMMANDS)
		sp = ha->outstanding_cmds[handle];
	else
		sp = NULL;

	if (sp) {

		ha->outstanding_cmds[handle] = NULL;


		if (pkt->entry_status & (BIT_3 + BIT_2)) {


			CMD_RESULT(sp->cmd) = DID_ERROR << 16;
		} else if (pkt->entry_status & BIT_1) {
			CMD_RESULT(sp->cmd) = DID_BUS_BUSY << 16;
		} else {

			CMD_RESULT(sp->cmd) = DID_ERROR << 16;
		}

		CMD_HANDLE(sp->cmd) = COMPLETED_HANDLE;


		list_add_tail(&sp->list, done_q);
	}
#ifdef QLA_64BIT_PTR
	else if (pkt->entry_type == COMMAND_A64_TYPE) {
		printk(KERN_WARNING "!qla1280: Error Entry invalid handle");
	}
#endif

	LEAVE("qla1280_error_entry");
}
