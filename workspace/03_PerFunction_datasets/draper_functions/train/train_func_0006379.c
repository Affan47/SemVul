slurm_get_controller_addr_spec(enum controller_id dest, slurm_addr_t *addr)
{
	addr = (dest == PRIMARY_CONTROLLER) ?
		&proto_conf->primary_controller :
		&proto_conf->secondary_controller;
}
