hashlimit_check(unsigned int flags)
{
	if (!(flags & PARAM_LIMIT))
		xtables_error(PARAMETER_PROBLEM,
				"You have to specify --hashlimit");
	if (!(flags & PARAM_MODE))
		xtables_error(PARAMETER_PROBLEM,
				"You have to specify --hashlimit-mode");
	if (!(flags & PARAM_NAME))
		xtables_error(PARAMETER_PROBLEM,
				"You have to specify --hashlimit-name");
}
