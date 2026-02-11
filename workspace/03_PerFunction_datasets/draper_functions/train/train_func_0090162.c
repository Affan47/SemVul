slurm_conf_get_cpus_bsct(const char *node_name,
				    uint16_t *cpus, uint16_t *boards,
				    uint16_t *sockets, uint16_t *cores,
				    uint16_t *threads)
{
	int idx;
	names_ll_t *p;

	slurm_conf_lock();
	_init_slurmd_nodehash();

	idx = _get_hash_idx(node_name);
	p = node_to_host_hashtbl[idx];
	while (p) {
		if (strcmp(p->alias, node_name) == 0) {
		    	if (cpus)
				*cpus    = p->cpus;
			if (boards)
				*boards  = p->boards;
			if (sockets)
				*sockets = p->sockets;
			if (cores)
				*cores   = p->cores;
			if (threads)
				*threads = p->threads;
			slurm_conf_unlock();
			return SLURM_SUCCESS;
		}
		p = p->next_alias;
	}
	slurm_conf_unlock();

	return SLURM_FAILURE;
}
