start_recv_msg_fetch(struct ssif_info *ssif_info,
				 unsigned long *flags)
{
	struct ipmi_smi_msg *msg;

	msg = ipmi_alloc_smi_msg();
	if (!msg) {
		ssif_info->ssif_state = SSIF_NORMAL;
		return;
	}

	ssif_info->curr_msg = msg;
	ssif_info->ssif_state = SSIF_GETTING_MESSAGES;
	ipmi_ssif_unlock_cond(ssif_info, flags);

	msg->data[0] = (IPMI_NETFN_APP_REQUEST << 2);
	msg->data[1] = IPMI_GET_MSG_CMD;
	msg->data_size = 2;

	check_start_send(ssif_info, flags, msg);
}
