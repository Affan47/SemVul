xpc_send_gru_msg(struct gru_message_queue_desc *gru_mq_desc, void *msg,
		 size_t msg_size)
{
	enum xp_retval xp_ret;
	int ret;

	while (1) {
		ret = gru_send_message_gpa(gru_mq_desc, msg, msg_size);
		if (ret == MQE_OK) {
			xp_ret = xpSuccess;
			break;
		}

		if (ret == MQE_QUEUE_FULL) {
			dev_dbg(xpc_chan, "gru_send_message_gpa() returned "
				"error=MQE_QUEUE_FULL\n");


			(void)msleep_interruptible(10);
		} else if (ret == MQE_CONGESTION) {
			dev_dbg(xpc_chan, "gru_send_message_gpa() returned "
				"error=MQE_CONGESTION\n");


		} else {

			dev_err(xpc_chan, "gru_send_message_gpa() returned "
				"error=%d\n", ret);
			xp_ret = xpGruSendMqError;
			break;
		}
	}
	return xp_ret;
}
