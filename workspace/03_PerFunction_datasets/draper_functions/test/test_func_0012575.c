__repmgr_set_membership(env, host, port, status, flags)
	ENV *env;
	const char *host;
	u_int port;
	u_int32_t status;
	u_int32_t flags;
{
	DB_REP *db_rep;
	REP *rep;
	REGINFO *infop;
	REPMGR_SITE *site;
	SITEINFO *sites;
	u_int32_t orig;
	int eid, ret;

	db_rep = env->rep_handle;
	rep = db_rep->region;
	infop = env->reginfo;

	COMPQUIET(orig, 0);
	COMPQUIET(site, NULL);
	DB_ASSERT(env, REP_ON(env));

	MUTEX_LOCK(env, rep->mtx_repmgr);
	if ((ret = get_eid(env, host, port, &eid)) == 0) {
		DB_ASSERT(env, IS_VALID_EID(eid));
		site = SITE_FROM_EID(eid);
		orig = site->membership;
		sites = R_ADDR(infop, rep->siteinfo_off);

		RPRINT(env, (env, DB_VERB_REPMGR_MISC,
		    "set membership for %s:%lu %lu (was %lu)",
		    host, (u_long)port, (u_long)status, (u_long)orig));
		if (status != sites[eid].status) {


			db_rep->siteinfo_seq = ++rep->siteinfo_seq;
		}


		site->membership = status;
		site->gmdb_flags = flags;
		sites[eid].status = status;
		sites[eid].flags = flags;
	}
	MUTEX_UNLOCK(env, rep->mtx_repmgr);


	if (ret == 0 && db_rep->repmgr_status == running &&
	    SELECTOR_RUNNING(db_rep)) {

		if (eid == db_rep->self_eid && status != SITE_PRESENT)
			ret = (status == SITE_ADDING) ?
			    __repmgr_defer_op(env, REPMGR_REJOIN) : DB_DELETED;
		else if (orig != SITE_PRESENT && status == SITE_PRESENT &&
		    site->state == SITE_IDLE) {


			ret = __repmgr_schedule_connection_attempt(env,
			    eid, TRUE);
			if (eid != db_rep->self_eid)
				DB_EVENT(env, DB_EVENT_REP_SITE_ADDED, &eid);
		} else if (orig != 0 && status == 0)
			DB_EVENT(env, DB_EVENT_REP_SITE_REMOVED, &eid);


	}
	return (ret);
}
