c_handle_config_update(const generic_config_flag_t *flags, int flags_nr,
		       const char *subsystem, int *active_options_p)
{
	int i;

	if (!_debugstate_valid) {
		sciprintf("Not in debug state\n");
		return 1;
	}

	if (cmd_paramlength == 0)
		handle_config_update(flags, flags_nr,
				     subsystem, active_options_p,
				     0);

	for (i = 0; i < cmd_paramlength; i++)
		handle_config_update(flags, flags_nr,
				     subsystem, active_options_p,
				     cmd_params[i].str);
	return 0;
}
