init_stats (simstats_t *stats, simulation_t *sim)
{
	stats->min        = g_new (gnm_float, sim->n_vars);
	stats->max        = g_new (gnm_float, sim->n_vars);
	stats->mean       = g_new (gnm_float, sim->n_vars);
	stats->median     = g_new (gnm_float, sim->n_vars);
	stats->mode       = g_new (gnm_float, sim->n_vars);
	stats->stddev     = g_new (gnm_float, sim->n_vars);
	stats->var        = g_new (gnm_float, sim->n_vars);
	stats->skew       = g_new (gnm_float, sim->n_vars);
	stats->kurtosis   = g_new (gnm_float, sim->n_vars);
	stats->range      = g_new (gnm_float, sim->n_vars);
	stats->confidence = g_new (gnm_float, sim->n_vars);
	stats->lower      = g_new (gnm_float, sim->n_vars);
	stats->upper      = g_new (gnm_float, sim->n_vars);
	stats->errmask    = g_new (int, sim->n_vars);
}
