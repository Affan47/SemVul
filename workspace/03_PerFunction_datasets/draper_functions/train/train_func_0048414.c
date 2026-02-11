free_rt_env(Var * rt_env, unsigned size)
{
    register unsigned i;

    for (i = 0; i < size; i++)
	free_var(rt_env[i]);

    if (size <= NUM_READY_VARS) {
	rt_env[0].v.list = ready_size_rt_envs;
	ready_size_rt_envs = rt_env;
    } else
	myfree((void *) rt_env, M_RT_ENV);
}
