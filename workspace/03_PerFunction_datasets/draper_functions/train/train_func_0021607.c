msg_to_slurmd (slurm_msg_type_t msg_type)
{
	int i;
	shutdown_msg_t *shutdown_req;
	agent_arg_t *kill_agent_args;
#ifdef HAVE_FRONT_END
	front_end_record_t *front_end_ptr;
#else
	struct node_record *node_ptr;
#endif

	kill_agent_args = xmalloc (sizeof (agent_arg_t));
	kill_agent_args->msg_type = msg_type;
	kill_agent_args->retry = 0;
	kill_agent_args->hostlist = hostlist_create("");
	if (kill_agent_args->hostlist == NULL)
		fatal("hostlist_create: malloc failure");
	if (msg_type == REQUEST_SHUTDOWN) {
 		shutdown_req = xmalloc(sizeof(shutdown_msg_t));
		shutdown_req->options = 0;
		kill_agent_args->msg_args = shutdown_req;
	}

#ifdef HAVE_FRONT_END
	for (i = 0, front_end_ptr = front_end_nodes;
	     i < front_end_node_cnt; i++, front_end_ptr++) {
		hostlist_push(kill_agent_args->hostlist, front_end_ptr->name);
		kill_agent_args->node_count++;
	}
#else
	node_ptr = node_record_table_ptr;
	for (i = 0; i < node_record_count; i++, node_ptr++) {
		if (IS_NODE_FUTURE(node_ptr))
			continue;
		if (IS_NODE_CLOUD(node_ptr) && IS_NODE_POWER_SAVE(node_ptr))
			continue;
		hostlist_push(kill_agent_args->hostlist, node_ptr->name);
		kill_agent_args->node_count++;
	}
#endif

	if (kill_agent_args->node_count == 0) {
		hostlist_destroy(kill_agent_args->hostlist);
		xfree (kill_agent_args);
	} else {
		debug ("Spawning agent msg_type=%d", msg_type);
		agent_queue_request(kill_agent_args);
	}
}
