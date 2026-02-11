scontrol_print_completing_job(job_info_t *job_ptr,
			      node_info_msg_t *node_info_msg)
{
	int i;
	node_info_t *node_info;
	hostlist_t all_nodes, comp_nodes, down_nodes;
	char *node_buf;

	all_nodes  = hostlist_create(job_ptr->nodes);
	comp_nodes = hostlist_create("");
	down_nodes = hostlist_create("");

	for (i=0; i<node_info_msg->record_count; i++) {
		node_info = &(node_info_msg->node_array[i]);
		if (IS_NODE_COMPLETING(node_info) &&
		    (_in_node_bit_list(i, job_ptr->node_inx)))
			hostlist_push_host(comp_nodes, node_info->name);
		else if (IS_NODE_DOWN(node_info) &&
			 (hostlist_find(all_nodes, node_info->name) != -1))
			hostlist_push_host(down_nodes, node_info->name);
	}

	fprintf(stdout, "JobId=%u ", job_ptr->job_id);

	node_buf = hostlist_ranged_string_xmalloc(comp_nodes);
	if (node_buf && node_buf[0])
		fprintf(stdout, "Nodes(COMPLETING)=%s ", node_buf);
	xfree(node_buf);

	node_buf = hostlist_ranged_string_xmalloc(down_nodes);
	if (node_buf && node_buf[0])
		fprintf(stdout, "Nodes(DOWN)=%s ", node_buf);
	xfree(node_buf);
	fprintf(stdout, "\n");

	hostlist_destroy(all_nodes);
	hostlist_destroy(comp_nodes);
	hostlist_destroy(down_nodes);
}
