add_extra_method_with_depth (MonoAotCompile *acfg, MonoMethod *method, int depth)
{
	if (mono_method_is_generic_sharable_full (method, TRUE, TRUE, FALSE))
		method = mini_get_shared_method (method);
	else if ((acfg->opts & MONO_OPT_GSHAREDVT) && prefer_gsharedvt_method (acfg, method) && mono_method_is_generic_sharable_full (method, FALSE, FALSE, TRUE))

		method = mini_get_shared_method_full (method, TRUE, TRUE);

	if (acfg->aot_opts.log_generics)
		aot_printf (acfg, "%*sAdding method %s.\n", depth, "", mono_method_full_name (method, TRUE));

	add_method_full (acfg, method, TRUE, depth);
}
