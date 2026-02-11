__rep_fire_startupdone(env, gen, master)
	ENV *env;
	u_int32_t gen;
	int master;
{
	DB_REP *db_rep;
	REP *rep;

	db_rep = env->rep_handle;
	rep = db_rep->region;

	REP_EVENT_LOCK(env);


	if (rep->newmaster_event_gen < gen) {
		__rep_fire_event(env, DB_EVENT_REP_NEWMASTER, &master);
		rep->newmaster_event_gen = gen;
	}


	if (rep->newmaster_event_gen == gen)
		__rep_fire_event(env, DB_EVENT_REP_STARTUPDONE, NULL);
	REP_EVENT_UNLOCK(env);
	return (0);
}
