ibv_cmd_destroy_qp(struct ibv_qp *qp)
{
	struct ibv_destroy_qp      cmd;
	struct ibv_destroy_qp_resp resp;

	if (abi_ver == 1)
		return ibv_cmd_destroy_qp_v1(qp);

	IBV_INIT_CMD_RESP(&cmd, sizeof cmd, DESTROY_QP, &resp, sizeof resp);
	cmd.qp_handle = qp->handle;
	cmd.reserved  = 0;

	if (write(qp->context->cmd_fd, &cmd, sizeof cmd) != sizeof cmd)
		return errno;

	(void) VALGRIND_MAKE_MEM_DEFINED(&resp, sizeof resp);

	pthread_mutex_lock(&qp->mutex);
	while (qp->events_completed != resp.events_reported)
		pthread_cond_wait(&qp->cond, &qp->mutex);
	pthread_mutex_unlock(&qp->mutex);

	return 0;
}
