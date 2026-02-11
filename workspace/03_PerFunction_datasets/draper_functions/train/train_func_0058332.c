__rep_check_doreq(env, rep)
	ENV *env;
	REP *rep;
{

	DB_LOG *dblp;
	LOG *lp;
	db_timespec now;
	int req;

	dblp = env->lg_handle;
	lp = dblp->reginfo.primary;
	__os_gettime(env, &now, 1);
	timespecsub(&now, &lp->rcvd_ts);
	req = timespeccmp(&now, &lp->wait_ts, >=);
	if (req) {


		timespecadd(&lp->wait_ts, &lp->wait_ts);
		if (timespeccmp(&lp->wait_ts, &rep->max_gap, >))
			lp->wait_ts = rep->max_gap;
		__os_gettime(env, &lp->rcvd_ts, 1);
	}
	return (req);
}
