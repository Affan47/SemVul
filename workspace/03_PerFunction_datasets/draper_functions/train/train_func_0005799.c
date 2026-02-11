_merge_synonym(struct cmd_context *cmd, int oldarg, int newarg)
{
	const struct arg_values *old;
	struct arg_values *new;

	if (arg_count(cmd, oldarg) && arg_count(cmd, newarg)) {
		log_error("%s and %s are synonyms.  Please only supply one.",
			  _cmdline.arg_props[oldarg].long_arg, _cmdline.arg_props[newarg].long_arg);
		return 0;
	}

	if (!arg_count(cmd, oldarg))
		return 1;

	old = cmd->arg_values + oldarg;
	new = cmd->arg_values + newarg;

	new->count = old->count;
	new->value = old->value;
	new->i_value = old->i_value;
	new->ui_value = old->ui_value;
	new->i64_value = old->i64_value;
	new->ui64_value = old->ui64_value;
	new->sign = old->sign;

	return 1;
}
