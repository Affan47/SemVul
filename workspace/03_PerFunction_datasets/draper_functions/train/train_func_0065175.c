cmdenv_arg(struct cmd_env *env)
{
	if (env->argp < env->argc)
		return env->argv[env->argp];
	if (env->argp == env->argc)
		return NEWLINE;
	return NULL;
}
