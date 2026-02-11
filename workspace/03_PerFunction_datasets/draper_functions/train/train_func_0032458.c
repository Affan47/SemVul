qla8044_serdes_op(struct fc_bsg_job *bsg_job)
{
	struct Scsi_Host *host = bsg_job->shost;
	scsi_qla_host_t *vha = shost_priv(host);
	int rval = 0;
	struct qla_serdes_reg_ex sr;

	memset(&sr, 0, sizeof(sr));

	sg_copy_to_buffer(bsg_job->request_payload.sg_list,
	    bsg_job->request_payload.sg_cnt, &sr, sizeof(sr));

	switch (sr.cmd) {
	case INT_SC_SERDES_WRITE_REG:
		rval = qla8044_write_serdes_word(vha, sr.addr, sr.val);
		bsg_job->reply->reply_payload_rcv_len = 0;
		break;
	case INT_SC_SERDES_READ_REG:
		rval = qla8044_read_serdes_word(vha, sr.addr, &sr.val);
		sg_copy_from_buffer(bsg_job->reply_payload.sg_list,
		    bsg_job->reply_payload.sg_cnt, &sr, sizeof(sr));
		bsg_job->reply->reply_payload_rcv_len = sizeof(sr);
		break;
	default:
		ql_dbg(ql_dbg_user, vha, 0x70cf,
		    "Unknown serdes cmd %x.\n", sr.cmd);
		rval = -EINVAL;
		break;
	}

	bsg_job->reply->reply_data.vendor_reply.vendor_rsp[0] =
	    rval ? EXT_STATUS_MAILBOX : 0;

	bsg_job->reply_len = sizeof(struct fc_bsg_reply);
	bsg_job->reply->result = DID_OK << 16;
	bsg_job->job_done(bsg_job);
	return 0;
}
