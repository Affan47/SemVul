slurm_reset_alias(char *node_name, char *node_addr,
			      char *node_hostname)
{
	int idx;
	names_ll_t *p;

	slurm_conf_lock();
	_init_slurmd_nodehash();

	idx = _get_hash_idx(node_name);
	p = node_to_host_hashtbl[idx];
	while (p) {
		if (strcmp(p->alias, node_name) == 0) {
			if (node_addr) {
				xfree(p->address);
				p->address = xstrdup(node_addr);
				p->addr_initialized = false;
			}
			if (node_hostname) {
				xfree(p->hostname);
				p->hostname = xstrdup(node_hostname);
			}
			break;
		}
		p = p->next_alias;
	}
	slurm_conf_unlock();

	return;
}
