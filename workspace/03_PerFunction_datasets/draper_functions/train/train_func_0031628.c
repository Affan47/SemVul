_init_slurmd_nodehash(void)
{
	slurm_conf_node_t **ptr_array;
	slurm_conf_frontend_t **ptr_front_end;
	int count, i;

	if (nodehash_initialized)
		return;
	else
		nodehash_initialized = true;

	if (!conf_initialized) {
		_init_slurm_conf(NULL);
		conf_initialized = true;
	}

	count = slurm_conf_nodename_array(&ptr_array);
	for (i = 0; i < count; i++)
		_register_conf_node_aliases(ptr_array[i]);

	count = slurm_conf_frontend_array(&ptr_front_end);
	for (i = 0; i < count; i++)
		_register_front_ends(ptr_front_end[i]);
}
