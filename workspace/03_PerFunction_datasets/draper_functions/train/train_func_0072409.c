__repmgr_connector_thread(argsp)
	void *argsp;
{
	ENV *env;
	DB_THREAD_INFO *ip;
	REPMGR_RUNNABLE *th;
	int ret;

	th = argsp;
	env = th->env;
	ip = NULL;
	ret = 0;

	ENV_ENTER_RET(env, ip, ret);
	if (ret == 0)
		RPRINT(env, (env, DB_VERB_REPMGR_MISC,
		    "starting connector thread, eid %u",
		    th->args.conn_th.eid));
	if (ret != 0 || (ret = __repmgr_connector_main(env, th)) != 0) {
		__db_err(env, ret, DB_STR("3617", "connector thread failed"));
		RPRINT(env, (env,
		    DB_VERB_REPMGR_MISC, "connector thread is exiting"));
		ENV_LEAVE(env, ip);
		(void)__repmgr_thread_failure(env, ret);
	}
	if (ret == 0) {
		RPRINT(env, (env,
		    DB_VERB_REPMGR_MISC, "connector thread is exiting"));
		ENV_LEAVE(env, ip);
	}
	th->finished = TRUE;
	return (NULL);
}
