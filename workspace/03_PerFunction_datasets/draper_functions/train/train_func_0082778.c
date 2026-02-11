start_config_manager(struct auditd_reply_list *rep)
{
	int retval, rc = 0;

	retval = pthread_mutex_trylock(&config_lock);
	if (retval == 0) {
		pthread_attr_t detached;

		pthread_attr_init(&detached);
		pthread_attr_setdetachstate(&detached,
			PTHREAD_CREATE_DETACHED);

	        if (pthread_create(&config_thread, &detached,
        	                config_thread_main, rep) < 0) {
                	audit_msg(LOG_ERR,
			"Couldn't create config thread, no config changes");
			free(rep);
			pthread_mutex_unlock(&config_lock);
        	        rc = 1;
	        }
		pthread_attr_destroy(&detached);
	} else {
               	audit_msg(LOG_ERR,
			"Config thread already running, no config changes");
		free(rep);
       	        rc = 1;
	}
	return rc;
}
