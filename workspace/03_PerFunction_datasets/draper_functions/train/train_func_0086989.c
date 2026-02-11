ibv_cmd_create_cq(struct ibv_context *context, int cqe,
		      struct ibv_comp_channel *channel,
		      int comp_vector, struct ibv_cq *cq,
		      struct ibv_create_cq *cmd, size_t cmd_size,
		      struct ibv_create_cq_resp *resp, size_t resp_size)
{
	IBV_INIT_CMD_RESP(cmd, cmd_size, CREATE_CQ, resp, resp_size);
	cmd->user_handle   = (uintptr_t) cq;
	cmd->cqe           = cqe;
	cmd->comp_vector   = comp_vector;
	cmd->comp_channel  = channel ? channel->fd : -1;
	cmd->reserved      = 0;

	if (write(context->cmd_fd, cmd, cmd_size) != cmd_size)
		return errno;

	(void) VALGRIND_MAKE_MEM_DEFINED(resp, resp_size);

	cq->handle  = resp->cq_handle;
	cq->cqe     = resp->cqe;
	cq->context = context;

	return 0;
}
