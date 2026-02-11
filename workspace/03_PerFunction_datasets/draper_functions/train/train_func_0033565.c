lo_rw_aio_complete(struct kiocb *iocb, long ret, long ret2)
{
	struct loop_cmd *cmd = container_of(iocb, struct loop_cmd, iocb);
	struct request *rq = cmd->rq;

	handle_partial_read(cmd, ret);

	if (ret > 0)
		ret = 0;
	else if (ret < 0)
		ret = -EIO;

	blk_mq_complete_request(rq, ret);
}
