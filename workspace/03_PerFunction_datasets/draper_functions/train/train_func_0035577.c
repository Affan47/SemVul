syncenv_scale (struct syncenv *env)
{
	int  diff = 0;
        int  scale = 0;
	int  i = 0;
	int  ret = 0;

	pthread_mutex_lock (&env->mutex);
	{
		if (env->procs > env->runcount)
			goto unlock;

                scale = env->runcount;
                if (scale > SYNCENV_PROC_MAX)
                        scale = SYNCENV_PROC_MAX;
                if (scale > env->procs)
                        diff = scale - env->procs;
                while (diff) {
                        diff--;
                        for (; (i < SYNCENV_PROC_MAX); i++) {
                                if (env->proc[i].processor == 0)
                                        break;
                        }

			env->proc[i].env = env;
			ret = pthread_create (&env->proc[i].processor, NULL,
					      syncenv_processor, &env->proc[i]);
			if (ret)
				break;
			env->procs++;
                        i++;
		}
	}
unlock:
	pthread_mutex_unlock (&env->mutex);
}
