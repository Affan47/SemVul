reload(void)
{
	if (clearglobalvars_config)
		pbx_builtin_clear_globals();
	return pbx_load_module();
}
