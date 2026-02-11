_node_did_resp(struct node_record *node_ptr)
{
	int node_inx;
	uint16_t node_flags;
	time_t now = time(NULL);

	node_inx = node_ptr - node_record_table_ptr;
	node_ptr->last_response = now;
	if (IS_NODE_NO_RESPOND(node_ptr) || IS_NODE_POWER_UP(node_ptr)) {
		info("Node %s now responding", node_ptr->name);
		node_ptr->node_state &= (~NODE_STATE_NO_RESPOND);
		node_ptr->node_state &= (~NODE_STATE_POWER_UP);
		if (!is_node_in_maint_reservation(node_inx))
			node_ptr->node_state &= (~NODE_STATE_MAINT);
		last_node_update = now;
	}
	node_flags = node_ptr->node_state & NODE_STATE_FLAGS;
	if (IS_NODE_UNKNOWN(node_ptr)) {
		node_ptr->last_idle = now;
		if (node_ptr->run_job_cnt) {
			node_ptr->node_state = NODE_STATE_ALLOCATED |
					       node_flags;
		} else
			node_ptr->node_state = NODE_STATE_IDLE | node_flags;
		last_node_update = now;
		if (!IS_NODE_DRAIN(node_ptr) && !IS_NODE_FAIL(node_ptr)) {
			clusteracct_storage_g_node_up(acct_db_conn,
						      node_ptr, now);
		}
	}
	if (IS_NODE_DOWN(node_ptr) &&
	    (slurmctld_conf.ret2service == 1) &&
	    (node_ptr->reason != NULL) &&
	    (strncmp(node_ptr->reason, "Not responding", 14) == 0)) {
		node_ptr->last_idle = now;
		node_ptr->node_state = NODE_STATE_IDLE | node_flags;
		info("node_did_resp: node %s returned to service",
		     node_ptr->name);
		trigger_node_up(node_ptr);
		last_node_update = now;
		if (!IS_NODE_DRAIN(node_ptr) && !IS_NODE_FAIL(node_ptr)) {


			clusteracct_storage_g_node_up(acct_db_conn,
						      node_ptr, now);
		}
	}
	if (IS_NODE_IDLE(node_ptr) && !IS_NODE_COMPLETING(node_ptr)) {
		bit_set (idle_node_bitmap, node_inx);
		bit_set (share_node_bitmap, node_inx);
	}
	if (IS_NODE_DOWN(node_ptr) || IS_NODE_DRAIN(node_ptr) ||
	    IS_NODE_FAIL(node_ptr)) {
		bit_clear (avail_node_bitmap, node_inx);
	} else
		bit_set   (avail_node_bitmap, node_inx);
	if (IS_NODE_DOWN(node_ptr))
		bit_clear (up_node_bitmap, node_inx);
	else
		bit_set   (up_node_bitmap, node_inx);
	return;
}
