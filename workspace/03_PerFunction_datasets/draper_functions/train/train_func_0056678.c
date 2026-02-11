host_int_wait_msg_queue_idle(void)
{
	int result = 0;
	struct host_if_msg msg;

	memset(&msg, 0, sizeof(struct host_if_msg));
	msg.id = HOST_IF_MSG_Q_IDLE;
	result = wilc_mq_send(&hif_msg_q, &msg, sizeof(struct host_if_msg));
	if (result) {
		PRINT_ER("wilc mq send fail\n");
		result = -EINVAL;
	}

	down(&hif_sema_wait_response);

	return result;
}
