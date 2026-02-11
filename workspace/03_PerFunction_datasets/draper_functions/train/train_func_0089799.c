emit_autoreg (MonoAotCompile *acfg)
{
	char *symbol;


	if (! (!acfg->use_bin_writer && acfg->aot_opts.static_link && acfg->aot_opts.autoreg))
		return;

	symbol = g_strdup_printf ("_%s_autoreg", acfg->static_linking_symbol);

	arch_emit_autoreg (acfg, symbol);

	g_free (symbol);
}
