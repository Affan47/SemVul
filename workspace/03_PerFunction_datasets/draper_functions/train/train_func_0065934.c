qla4xxx_restore_defaults(struct bsg_job *bsg_job)
{
	struct Scsi_Host *host = iscsi_job_to_shost(bsg_job);
	struct scsi_qla_host *ha = to_qla_host(host);
	struct iscsi_bsg_request *bsg_req = bsg_job->request;
	struct iscsi_bsg_reply *bsg_reply = bsg_job->reply;
	uint32_t region = 0;
	uint32_t field0 = 0;
	uint32_t field1 = 0;
	int rval = -EINVAL;

	bsg_reply->reply_payload_rcv_len = 0;

	if (unlikely(pci_channel_offline(ha->pdev)))
		goto leave;

	if (is_qla4010(ha))
		goto leave;

	if (ql4xxx_reset_active(ha)) {
		ql4_printk(KERN_ERR, ha, "%s: reset active\n", __func__);
		rval = -EBUSY;
		goto leave;
	}

	region = bsg_req->rqst_data.h_vendor.vendor_cmd[1];
	field0 = bsg_req->rqst_data.h_vendor.vendor_cmd[2];
	field1 = bsg_req->rqst_data.h_vendor.vendor_cmd[3];

	rval = qla4xxx_restore_factory_defaults(ha, region, field0, field1);
	if (rval) {
		ql4_printk(KERN_ERR, ha, "%s: set nvram failed\n", __func__);
		bsg_reply->result = DID_ERROR << 16;
		rval = -EIO;
	} else
		bsg_reply->result = DID_OK << 16;

	bsg_job_done(bsg_job, bsg_reply->result,
		     bsg_reply->reply_payload_rcv_len);
leave:
	return rval;
}
