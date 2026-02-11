dlm_begin_exit_domain_handler(struct o2net_msg *msg, u32 len,
					 void *data, void **ret_data)
{
	struct dlm_ctxt *dlm = data;
	unsigned int node;
	struct dlm_exit_domain *exit_msg = (struct dlm_exit_domain *) msg->buf;

	if (!dlm_grab(dlm))
		return 0;

	node = exit_msg->node_idx;
	mlog(0, "%s: Node %u sent a begin exit domain message\n", dlm->name, node);

	spin_lock(&dlm->spinlock);
	set_bit(node, dlm->exit_domain_map);
	spin_unlock(&dlm->spinlock);

	dlm_put(dlm);

	return 0;
}
