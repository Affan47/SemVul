__rep_skip_msg(env, rep, eid, rectype)
	ENV *env;
	REP *rep;
	int eid;
	u_int32_t rectype;
{
	int do_req, ret;

	ret = 0;


	if (F_ISSET(rep, REP_F_CLIENT) && REP_MSG_REQ(rectype))
		do_req = 1;
	else {

		MUTEX_LOCK(env, rep->mtx_clientdb);
		do_req = __rep_check_doreq(env, rep);
		MUTEX_UNLOCK(env, rep->mtx_clientdb);
	}


	if (do_req && rectype != REP_MASTER_REQ) {


		if (rep->master_id == DB_EID_INVALID)
			(void)__rep_send_message(env,
			    DB_EID_BROADCAST, REP_MASTER_REQ, NULL, NULL, 0, 0);
		else if (eid == rep->master_id)
			ret = __rep_resend_req(env, 0);
		else if (F_ISSET(rep, REP_F_CLIENT))
			(void)__rep_send_message(env,
			    eid, REP_REREQUEST, NULL, NULL, 0, 0);
	}
	return (ret);
}
