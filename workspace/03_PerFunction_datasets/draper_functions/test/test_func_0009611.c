loop_handle_cmd(struct loop_cmd *cmd)
{
	const bool write = cmd->rq->cmd_flags & REQ_WRITE;
	struct loop_device *lo = cmd->rq->q->queuedata;
	int ret = 0;

	if (write && (lo->lo_flags & LO_FLAGS_READ_ONLY)) {
		ret = -EIO;
		goto failed;
	}

	ret = do_req_filebacked(lo, cmd->rq);
 failed:

	if (!cmd->use_aio || ret)
		blk_mq_complete_request(cmd->rq, ret ? -EIO : 0);
}
