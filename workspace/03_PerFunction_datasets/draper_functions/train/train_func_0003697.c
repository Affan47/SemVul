dlm_send_one_domain_exit(struct dlm_ctxt *dlm, u32 msg_type,
				    unsigned int node)
{
	int status;
	struct dlm_exit_domain leave_msg;

	mlog(0, "%s: Sending domain exit message %u to node %u\n", dlm->name,
	     msg_type, node);

	memset(&leave_msg, 0, sizeof(leave_msg));
	leave_msg.node_idx = dlm->node_num;

	status = o2net_send_message(msg_type, dlm->key, &leave_msg,
				    sizeof(leave_msg), node, NULL);
	if (status < 0)
		mlog(ML_ERROR, "Error %d sending domain exit message %u "
		     "to node %u on domain %s\n", status, msg_type, node,
		     dlm->name);

	return status;
}
