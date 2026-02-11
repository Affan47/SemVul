__repmgr_sync_siteaddr(env)
	ENV *env;
{
	DB_REP *db_rep;
	REP *rep;
	u_int added;
	int ret;

	db_rep = env->rep_handle;
	rep = db_rep->region;

	ret = 0;

	MUTEX_LOCK(env, rep->mtx_repmgr);

	if (!IS_VALID_EID(db_rep->self_eid))
		db_rep->self_eid = rep->self_eid;

	added = db_rep->site_cnt;
	if ((ret = __repmgr_copy_in_added_sites(env)) == 0)
		ret = __repmgr_init_new_sites(env, (int)added,
		    (int)db_rep->site_cnt);

	MUTEX_UNLOCK(env, rep->mtx_repmgr);
	return (ret);
}
