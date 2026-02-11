acct_gather_energy_g_conf_values(void *data)
{
	if (slurm_acct_gather_energy_init() < 0)
		return;

	(*(ops.conf_values))(data);
}
