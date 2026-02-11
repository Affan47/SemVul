__repmgr_init_new_sites(env, from, limit)
	ENV *env;
	int from, limit;
{
	DB_REP *db_rep;
	REPMGR_SITE *site;
	int i, ret;

	db_rep = env->rep_handle;

	if (db_rep->selector == NULL)
		return (0);

	DB_ASSERT(env, IS_VALID_EID(from) && IS_VALID_EID(limit) &&
	    from <= limit);
	for (i = from; i < limit; i++) {
		site = SITE_FROM_EID(i);
		if (site->membership == SITE_PRESENT &&
		    (ret = __repmgr_schedule_connection_attempt(env,
		    i, TRUE)) != 0)
			return (ret);
	}

	return (0);
}
