__env_panic_set(env, on)
	ENV *env;
	int on;
{
	if (env != NULL && env->reginfo != NULL)
		((REGENV *)env->reginfo->primary)->panic = on ? 1 : 0;
}
