check_start_send(struct ssif_info *ssif_info, unsigned long *flags,
			     struct ipmi_smi_msg *msg)
{
	if (start_send(ssif_info, msg->data, msg->data_size) != 0) {
		unsigned long oflags;

		flags = ipmi_ssif_lock_cond(ssif_info, &oflags);
		ssif_info->curr_msg = NULL;
		ssif_info->ssif_state = SSIF_NORMAL;
		ipmi_ssif_unlock_cond(ssif_info, flags);
		ipmi_free_smi_msg(msg);
	}
}
