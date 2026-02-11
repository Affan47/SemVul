_slurm_crypto_init(void)
{
	char    *plugin_type = "crypto";
	char	*type = NULL;
	int	retval = SLURM_SUCCESS;

	if ( init_run && g_context )
		return retval;

	slurm_mutex_lock( &g_context_lock );
	if (crypto_restart_time == (time_t) 0)
		crypto_restart_time = time(NULL);
	if ( g_context )
		goto done;

	type = slurm_get_crypto_type();
	g_context = plugin_context_create(
		plugin_type, type, (void **)&ops, syms, sizeof(syms));

	if (!g_context) {
		error("cannot create %s context for %s", plugin_type, type);
		retval = SLURM_ERROR;
		goto done;
	}
	sbcast_cache_list = list_create(_sbcast_cache_del);
	init_run = true;

done:
	slurm_mutex_unlock( &g_context_lock );
	xfree(type);

	return(retval);
}
