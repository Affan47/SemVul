acct_gather_energy_p_update_node_energy(void)
{
	int rc = SLURM_SUCCESS;

	xassert(_run_in_daemon());

	if (local_energy->current_watts == NO_VAL)
		return rc;

	_get_joules_task(local_energy);

	return rc;
}
