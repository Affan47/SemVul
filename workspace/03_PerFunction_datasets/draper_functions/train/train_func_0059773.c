dlm_send_one_join_cancel(struct dlm_ctxt *dlm,
				    unsigned int node)
{
	int status;
	struct dlm_cancel_join cancel_msg;

	memset(&cancel_msg, 0, sizeof(cancel_msg));
	cancel_msg.node_idx = dlm->node_num;
	cancel_msg.name_len = strlen(dlm->name);
	memcpy(cancel_msg.domain, dlm->name, cancel_msg.name_len);

	status = o2net_send_message(DLM_CANCEL_JOIN_MSG, DLM_MOD_KEY,
				    &cancel_msg, sizeof(cancel_msg), node,
				    NULL);
	if (status < 0) {
		mlog(ML_ERROR, "Error %d when sending message %u (key 0x%x) to "
		     "node %u\n", status, DLM_CANCEL_JOIN_MSG, DLM_MOD_KEY,
		     node);
		goto bail;
	}

bail:
	return status;
}
