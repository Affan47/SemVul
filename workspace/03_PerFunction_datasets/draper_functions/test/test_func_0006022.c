_timer_thread(void *args)
{
	int i, now, diff;
	DEF_TIMERS;
	while (acct_gather_profile_running) {
		START_TIMER;
		now = time(NULL);

		for (i=0; i<PROFILE_CNT; i++) {
			if (acct_gather_suspended) {


				if (!acct_gather_profile_timer[i].freq)
					continue;
				if (acct_gather_profile_timer[i].last_notify)
					acct_gather_profile_timer[i].
						last_notify += SLEEP_TIME;
				else
					acct_gather_profile_timer[i].
						last_notify = now;
				continue;
			}

			diff = now - acct_gather_profile_timer[i].last_notify;


			if (!acct_gather_profile_timer[i].freq
			    || (diff < acct_gather_profile_timer[i].freq))
				continue;
			debug2("profile signalling type %s",
			       acct_gather_profile_type_t_name(i));


			slurm_mutex_lock(&acct_gather_profile_timer[i].
					 notify_mutex);
			pthread_cond_signal(
				&acct_gather_profile_timer[i].notify);
			slurm_mutex_unlock(&acct_gather_profile_timer[i].
					   notify_mutex);
			acct_gather_profile_timer[i].last_notify = now;
		}
		END_TIMER;
		usleep(USLEEP_TIME - DELTA_TIMER);
	}

	return NULL;
}
