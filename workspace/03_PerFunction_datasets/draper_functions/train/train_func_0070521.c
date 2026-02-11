__repmgr_init_election(env, flags)
	ENV *env;
	u_int32_t flags;
{
	DB_REP *db_rep;
	REPMGR_RUNNABLE *th;
	int ret;
	u_int i, new_size;

	COMPQUIET(th, NULL);

	db_rep = env->rep_handle;
	if (db_rep->repmgr_status == stopped) {
		RPRINT(env, (env, DB_VERB_REPMGR_MISC,
		    "ignoring elect thread request %#lx; repmgr is stopped",
		    (u_long)flags));
		return (0);
	}


	for (i = 0; i < db_rep->aelect_threads; i++) {
		th = db_rep->elect_threads[i];
		if (th == NULL)
			break;
		if (th->finished) {
			if ((ret = __repmgr_thread_join(th)) != 0)
				return (ret);

			break;
		}
	}
	if (i == db_rep->aelect_threads) {
		new_size = db_rep->aelect_threads + 1;
		if ((ret = __os_realloc(env,
		    sizeof(REPMGR_RUNNABLE*) * new_size,
		    &db_rep->elect_threads)) != 0)
			return (ret);
		db_rep->aelect_threads = new_size;
		STAT(db_rep->region->mstat.st_max_elect_threads = new_size);
		th = db_rep->elect_threads[i] = NULL;
	}

	if (th == NULL &&
	    (ret = __os_malloc(env, sizeof(REPMGR_RUNNABLE), &th)) != 0)
		return (ret);
	th->run = __repmgr_elect_thread;
	th->args.flags = flags;

	if ((ret = __repmgr_thread_start(env, th)) == 0)
		STAT(db_rep->region->mstat.st_elect_threads++);
	else {
		__os_free(env, th);
		th = NULL;
	}
	db_rep->elect_threads[i] = th;

	return (ret);
}
