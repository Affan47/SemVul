syncenv_scale (struct syncenv *env)
{
	int  thmax = 0;
	int  i = 0;
	int  ret = 0;

	pthread_mutex_lock (&env->mutex);
	{
		if (env->procs > env->runcount)
			goto unlock;

		thmax = min (env->runcount, SYNCENV_PROC_MAX);
		for (i = env->procs; i < thmax; i++) {
			env->proc[i].env = env;
			ret = pthread_create (&env->proc[i].processor, NULL,
					      syncenv_processor, &env->proc[i]);
			if (ret)
				break;
			env->procs++;
		}
	}
unlock:
	pthread_mutex_unlock (&env->mutex);
}
