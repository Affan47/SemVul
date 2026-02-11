__repmgr_autostart(env)
	ENV *env;
{
	DB_REP *db_rep;
	REP *rep;
	int ret;

	db_rep = env->rep_handle;
	rep = db_rep->region;

	DB_ASSERT(env, REP_ON(env));
	LOCK_MUTEX(db_rep->mutex);

	if (REPMGR_INITED(db_rep))
		ret = 0;
	else
		ret = __repmgr_init(env);
	if (ret != 0)
		goto out;

	RPRINT(env, (env, DB_VERB_REPMGR_MISC,
	    "Automatically joining existing repmgr env"));


	db_rep->self_eid = rep->eid;
	if ((ret = __rep_set_transport_int(env,
	    db_rep->self_eid, __repmgr_send)) != 0)
		goto out;

	if (db_rep->selector == NULL && db_rep->repmgr_status != running)
		ret = __repmgr_start_selector(env);

out:
	UNLOCK_MUTEX(db_rep->mutex);
	return (ret);
}
