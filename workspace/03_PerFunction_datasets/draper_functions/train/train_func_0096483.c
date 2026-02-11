qla2x00_write_i2c(struct fc_bsg_job *bsg_job)
{
	struct Scsi_Host *host = bsg_job->shost;
	scsi_qla_host_t *vha = shost_priv(host);
	struct qla_hw_data *ha = vha->hw;
	int rval = 0;
	uint8_t bsg[DMA_POOL_SIZE];
	struct qla_i2c_access *i2c = (void *)bsg;
	dma_addr_t sfp_dma;
	uint8_t *sfp = dma_pool_alloc(ha->s_dma_pool, GFP_KERNEL, &sfp_dma);
	if (!sfp) {
		bsg_job->reply->reply_data.vendor_reply.vendor_rsp[0] =
		    EXT_STATUS_NO_MEMORY;
		goto done;
	}

	sg_copy_to_buffer(bsg_job->request_payload.sg_list,
	    bsg_job->request_payload.sg_cnt, i2c, sizeof(*i2c));

	memcpy(sfp, i2c->buffer, i2c->length);
	rval = qla2x00_write_sfp(vha, sfp_dma, sfp,
	    i2c->device, i2c->offset, i2c->length, i2c->option);

	if (rval) {
		bsg_job->reply->reply_data.vendor_reply.vendor_rsp[0] =
		    EXT_STATUS_MAILBOX;
		goto dealloc;
	}

	bsg_job->reply->reply_data.vendor_reply.vendor_rsp[0] = 0;

dealloc:
	dma_pool_free(ha->s_dma_pool, sfp, sfp_dma);

done:
	bsg_job->reply_len = sizeof(struct fc_bsg_reply);
	bsg_job->reply->result = DID_OK << 16;
	bsg_job->job_done(bsg_job);

	return 0;
}
