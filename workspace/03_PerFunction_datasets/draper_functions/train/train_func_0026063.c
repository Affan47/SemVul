slurm_free_resource_allocation_response_msg (
	resource_allocation_response_msg_t * msg)
{
	if (msg) {
		select_g_select_jobinfo_free(msg->select_jobinfo);
		msg->select_jobinfo = NULL;
		xfree(msg->alias_list);
		xfree(msg->node_list);
		xfree(msg->cpus_per_node);
		xfree(msg->cpu_count_reps);
		xfree(msg);
	}
}
