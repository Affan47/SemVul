set_cluster_cpus(void)
{
	uint32_t cpus = 0;
	struct node_record *node_ptr;
	int i;

	node_ptr = node_record_table_ptr;
	for (i = 0; i < node_record_count; i++, node_ptr++) {
		if (node_ptr->name == '\0')
			continue;
#ifdef SLURM_NODE_ACCT_REGISTER
		if (slurmctld_conf.fast_schedule)
			cpus += node_ptr->config_ptr->cpus;
		else
			cpus += node_ptr->cpus;
#else
		cpus += node_ptr->config_ptr->cpus;
#endif
	}


	cluster_cpus = cpus;
}
