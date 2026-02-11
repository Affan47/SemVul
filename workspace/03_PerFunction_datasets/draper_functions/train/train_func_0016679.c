qla4xxx_read_flash(struct bsg_job *bsg_job)
{
	struct Scsi_Host *host = iscsi_job_to_shost(bsg_job);
	struct scsi_qla_host *ha = to_qla_host(host);
	struct iscsi_bsg_reply *bsg_reply = bsg_job->reply;
	struct iscsi_bsg_request *bsg_req = bsg_job->request;
	uint32_t offset = 0;
	uint32_t length = 0;
	dma_addr_t flash_dma;
	uint8_t *flash = NULL;
	int rval = -EINVAL;

	bsg_reply->reply_payload_rcv_len = 0;

	if (unlikely(pci_channel_offline(ha->pdev)))
		goto leave;

	if (ql4xxx_reset_active(ha)) {
		ql4_printk(KERN_ERR, ha, "%s: reset active\n", __func__);
		rval = -EBUSY;
		goto leave;
	}

	if (ha->flash_state != QLFLASH_WAITING) {
		ql4_printk(KERN_ERR, ha, "%s: another flash operation "
			   "active\n", __func__);
		rval = -EBUSY;
		goto leave;
	}

	ha->flash_state = QLFLASH_READING;
	offset = bsg_req->rqst_data.h_vendor.vendor_cmd[1];
	length = bsg_job->reply_payload.payload_len;

	flash = dma_alloc_coherent(&ha->pdev->dev, length, &flash_dma,
				   GFP_KERNEL);
	if (!flash) {
		ql4_printk(KERN_ERR, ha, "%s: dma alloc failed for flash "
			   "data\n", __func__);
		rval = -ENOMEM;
		goto leave;
	}

	rval = qla4xxx_get_flash(ha, flash_dma, offset, length);
	if (rval) {
		ql4_printk(KERN_ERR, ha, "%s: get flash failed\n", __func__);
		bsg_reply->result = DID_ERROR << 16;
		rval = -EIO;
	} else {
		bsg_reply->reply_payload_rcv_len =
			sg_copy_from_buffer(bsg_job->reply_payload.sg_list,
					    bsg_job->reply_payload.sg_cnt,
					    flash, length);
		bsg_reply->result = DID_OK << 16;
	}

	bsg_job_done(bsg_job, bsg_reply->result,
		     bsg_reply->reply_payload_rcv_len);
	dma_free_coherent(&ha->pdev->dev, length, flash, flash_dma);
leave:
	ha->flash_state = QLFLASH_WAITING;
	return rval;
}
