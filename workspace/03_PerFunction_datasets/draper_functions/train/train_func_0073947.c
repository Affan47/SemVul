nvme_alloc_request(struct request_queue *q,
		struct nvme_command *cmd, unsigned int flags, int qid)
{
	struct request *req;

	if (qid == NVME_QID_ANY) {
		req = blk_mq_alloc_request(q, nvme_is_write(cmd), flags);
	} else {
		req = blk_mq_alloc_request_hctx(q, nvme_is_write(cmd), flags,
				qid ? qid - 1 : 0);
	}
	if (IS_ERR(req))
		return req;

	req->cmd_type = REQ_TYPE_DRV_PRIV;
	req->cmd_flags |= REQ_FAILFAST_DRIVER;
	req->__data_len = 0;
	req->__sector = (sector_t) -1;
	req->bio = req->biotail = NULL;

	req->cmd = (unsigned char *)cmd;
	req->cmd_len = sizeof(struct nvme_command);

	return req;
}
