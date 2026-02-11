smscore_configure_board(struct smscore_device_t *coredev)
{
	struct sms_board *board;

	board = sms_get_board(coredev->board_id);
	if (!board) {
		pr_err("no board configuration exist.\n");
		return -EINVAL;
	}

	if (board->mtu) {
		struct sms_msg_data mtu_msg;
		pr_debug("set max transmit unit %d\n", board->mtu);

		mtu_msg.x_msg_header.msg_src_id = 0;
		mtu_msg.x_msg_header.msg_dst_id = HIF_TASK;
		mtu_msg.x_msg_header.msg_flags = 0;
		mtu_msg.x_msg_header.msg_type = MSG_SMS_SET_MAX_TX_MSG_LEN_REQ;
		mtu_msg.x_msg_header.msg_length = sizeof(mtu_msg);
		mtu_msg.msg_data[0] = board->mtu;

		coredev->sendrequest_handler(coredev->context, &mtu_msg,
					     sizeof(mtu_msg));
	}

	if (board->crystal) {
		struct sms_msg_data crys_msg;
		pr_debug("set crystal value %d\n", board->crystal);

		SMS_INIT_MSG(&crys_msg.x_msg_header,
				MSG_SMS_NEW_CRYSTAL_REQ,
				sizeof(crys_msg));
		crys_msg.msg_data[0] = board->crystal;

		coredev->sendrequest_handler(coredev->context, &crys_msg,
					     sizeof(crys_msg));
	}

	return 0;
}
