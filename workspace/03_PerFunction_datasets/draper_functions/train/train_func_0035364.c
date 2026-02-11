hptiop_queuecommand_lck(struct scsi_cmnd *scp,
				void (*done)(struct scsi_cmnd *))
{
	struct Scsi_Host *host = scp->device->host;
	struct hptiop_hba *hba = (struct hptiop_hba *)host->hostdata;
	struct hpt_iop_request_scsi_command *req;
	int sg_count = 0;
	struct hptiop_request *_req;

	BUG_ON(!done);
	scp->scsi_done = done;

	_req = get_req(hba);
	if (_req == NULL) {
		dprintk("hptiop_queuecmd : no free req\n");
		return SCSI_MLQUEUE_HOST_BUSY;
	}

	_req->scp = scp;

	dprintk("hptiop_queuecmd(scp=%p) %d/%d/%d/%llu cdb=(%08x-%08x-%08x-%08x) "
			"req_index=%d, req=%p\n",
			scp,
			host->host_no, scp->device->channel,
			scp->device->id, scp->device->lun,
			cpu_to_be32(((u32 *)scp->cmnd)[0]),
			cpu_to_be32(((u32 *)scp->cmnd)[1]),
			cpu_to_be32(((u32 *)scp->cmnd)[2]),
			cpu_to_be32(((u32 *)scp->cmnd)[3]),
			_req->index, _req->req_virt);

	scp->result = 0;

	if (scp->device->channel ||
			(scp->device->id > hba->max_devices) ||
			((scp->device->id == (hba->max_devices-1)) && scp->device->lun)) {
		scp->result = DID_BAD_TARGET << 16;
		free_req(hba, _req);
		goto cmd_done;
	}

	req = _req->req_virt;


	sg_count = hptiop_buildsgl(scp, req->sg_list);
	if (!sg_count)
		HPT_SCP(scp)->mapped = 0;

	req->header.flags = cpu_to_le32(IOP_REQUEST_FLAG_OUTPUT_CONTEXT);
	req->header.type = cpu_to_le32(IOP_REQUEST_TYPE_SCSI_COMMAND);
	req->header.result = cpu_to_le32(IOP_RESULT_PENDING);
	req->dataxfer_length = cpu_to_le32(scsi_bufflen(scp));
	req->channel = scp->device->channel;
	req->target = scp->device->id;
	req->lun = scp->device->lun;
	req->header.size = cpu_to_le32(
				sizeof(struct hpt_iop_request_scsi_command)
				 - sizeof(struct hpt_iopsg)
				 + sg_count * sizeof(struct hpt_iopsg));

	memcpy(req->cdb, scp->cmnd, sizeof(req->cdb));
	hba->ops->post_req(hba, _req);
	return 0;

cmd_done:
	dprintk("scsi_done(scp=%p)\n", scp);
	scp->scsi_done(scp);
	return 0;
}
