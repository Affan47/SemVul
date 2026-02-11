pscsi_execute_cmd(struct se_cmd *cmd)
{
	struct scatterlist *sgl = cmd->t_data_sg;
	u32 sgl_nents = cmd->t_data_nents;
	enum dma_data_direction data_direction = cmd->data_direction;
	struct pscsi_dev_virt *pdv = PSCSI_DEV(cmd->se_dev);
	struct pscsi_plugin_task *pt;
	struct request *req;
	struct bio *hbio;
	sense_reason_t ret;


	pt = kzalloc(sizeof(*pt) + scsi_command_size(cmd->t_task_cdb), GFP_KERNEL);
	if (!pt) {
		return TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
	}
	cmd->priv = pt;

	memcpy(pt->pscsi_cdb, cmd->t_task_cdb,
		scsi_command_size(cmd->t_task_cdb));

	if (!sgl) {
		req = blk_get_request(pdv->pdv_sd->request_queue,
				(data_direction == DMA_TO_DEVICE),
				GFP_KERNEL);
		if (IS_ERR(req)) {
			pr_err("PSCSI: blk_get_request() failed\n");
			ret = TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
			goto fail;
		}

		blk_rq_set_block_pc(req);
	} else {
		BUG_ON(!cmd->data_length);

		ret = pscsi_map_sg(cmd, sgl, sgl_nents, data_direction, &hbio);
		if (ret)
			goto fail;

		req = blk_make_request(pdv->pdv_sd->request_queue, hbio,
				       GFP_KERNEL);
		if (IS_ERR(req)) {
			pr_err("pSCSI: blk_make_request() failed\n");
			ret = TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
			goto fail_free_bio;
		}
	}

	req->end_io = pscsi_req_done;
	req->end_io_data = cmd;
	req->cmd_len = scsi_command_size(pt->pscsi_cdb);
	req->cmd = &pt->pscsi_cdb[0];
	req->sense = &pt->pscsi_sense[0];
	req->sense_len = 0;
	if (pdv->pdv_sd->type == TYPE_DISK)
		req->timeout = PS_TIMEOUT_DISK;
	else
		req->timeout = PS_TIMEOUT_OTHER;
	req->retries = PS_RETRY;

	blk_execute_rq_nowait(pdv->pdv_sd->request_queue, NULL, req,
			(cmd->sam_task_attr == TCM_HEAD_TAG),
			pscsi_req_done);

	return 0;

fail_free_bio:
	while (hbio) {
		struct bio *bio = hbio;
		hbio = hbio->bi_next;
		bio_endio(bio);
	}
	ret = TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
fail:
	kfree(pt);
	return ret;
}
