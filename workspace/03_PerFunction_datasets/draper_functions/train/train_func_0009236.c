redirect_and_varexp_helper(char ***new_env_p,
		struct variable **old_vars_p,
		struct command *command,
		int squirrel[3],
		char **argv_expanded)
{


	int rcode = setup_redirects(command, squirrel);
	if (rcode == 0) {
		char **new_env = expand_assignments(command->argv, command->assignment_cnt);
		*new_env_p = new_env;
		dump_cmd_in_x_mode(new_env);
		dump_cmd_in_x_mode(argv_expanded);
		if (old_vars_p)
			*old_vars_p = set_vars_and_save_old(new_env);
	}
	return rcode;
}
