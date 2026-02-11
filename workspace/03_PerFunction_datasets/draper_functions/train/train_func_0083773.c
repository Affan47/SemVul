ql4xxx_execute_diag_cmd(struct bsg_job *bsg_job)
{
	struct Scsi_Host *host = iscsi_job_to_shost(bsg_job);
	struct scsi_qla_host *ha = to_qla_host(host);
	struct iscsi_bsg_request *bsg_req = bsg_job->request;
	struct iscsi_bsg_reply *bsg_reply = bsg_job->reply;
	uint8_t *rsp_ptr = NULL;
	uint32_t mbox_cmd[MBOX_REG_COUNT];
	uint32_t mbox_sts[MBOX_REG_COUNT];
	int status = QLA_ERROR;

	DEBUG2(ql4_printk(KERN_INFO, ha, "%s: in\n", __func__));

	if (test_bit(DPC_RESET_HA, &ha->dpc_flags)) {
		ql4_printk(KERN_INFO, ha, "%s: Adapter reset in progress. Invalid Request\n",
			   __func__);
		bsg_reply->result = DID_ERROR << 16;
		goto exit_diag_mem_test;
	}

	bsg_reply->reply_payload_rcv_len = 0;
	memcpy(mbox_cmd, &bsg_req->rqst_data.h_vendor.vendor_cmd[1],
	       sizeof(uint32_t) * MBOX_REG_COUNT);

	DEBUG2(ql4_printk(KERN_INFO, ha,
			  "%s: mbox_cmd: %08X %08X %08X %08X %08X %08X %08X %08X\n",
			  __func__, mbox_cmd[0], mbox_cmd[1], mbox_cmd[2],
			  mbox_cmd[3], mbox_cmd[4], mbox_cmd[5], mbox_cmd[6],
			  mbox_cmd[7]));

	status = qla4xxx_mailbox_command(ha, MBOX_REG_COUNT, 8, &mbox_cmd[0],
					 &mbox_sts[0]);

	DEBUG2(ql4_printk(KERN_INFO, ha,
			  "%s: mbox_sts: %08X %08X %08X %08X %08X %08X %08X %08X\n",
			  __func__, mbox_sts[0], mbox_sts[1], mbox_sts[2],
			  mbox_sts[3], mbox_sts[4], mbox_sts[5], mbox_sts[6],
			  mbox_sts[7]));

	if (status == QLA_SUCCESS)
		bsg_reply->result = DID_OK << 16;
	else
		bsg_reply->result = DID_ERROR << 16;


	bsg_job->reply_len = sizeof(struct iscsi_bsg_reply) + sizeof(mbox_sts);
	rsp_ptr = ((uint8_t *)bsg_reply) + sizeof(struct iscsi_bsg_reply);
	memcpy(rsp_ptr, mbox_sts, sizeof(mbox_sts));

exit_diag_mem_test:
	DEBUG2(ql4_printk(KERN_INFO, ha,
			  "%s: bsg_reply->result = x%x, status = %s\n",
			  __func__, bsg_reply->result, STATUS(status)));

	bsg_job_done(bsg_job, bsg_reply->result,
		     bsg_reply->reply_payload_rcv_len);
}
