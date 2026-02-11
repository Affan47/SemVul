session_set_backend(struct session *s, struct proxy *be)
{
	if (s->flags & SN_BE_ASSIGNED)
		return 1;
	s->be = be;
	be->beconn++;
	if (be->beconn > be->be_counters.conn_max)
		be->be_counters.conn_max = be->beconn;
	proxy_inc_be_ctr(be);


	s->si[1].flags &= ~SI_FL_INDEP_STR;
	if (be->options2 & PR_O2_INDEPSTR)
		s->si[1].flags |= SI_FL_INDEP_STR;

	if (be->options2 & PR_O2_RSPBUG_OK)
		s->txn.rsp.err_pos = -1;
	s->flags |= SN_BE_ASSIGNED;


	if (unlikely(!s->txn.hdr_idx.v && be->http_needed)) {
		s->txn.hdr_idx.size = global.tune.max_http_hdr;
		if ((s->txn.hdr_idx.v = pool_alloc2(pool2_hdr_idx)) == NULL)
			return 0;


		http_init_txn(s);
	}


	if (s->fe->mode == PR_MODE_HTTP && be->mode == PR_MODE_HTTP &&
	    ((s->fe->options & PR_O_HTTP_MODE) != (be->options & PR_O_HTTP_MODE)))
		http_adjust_conn_mode(s, &s->txn, &s->txn.req);


	if (be->mode == PR_MODE_HTTP &&
	    (be->lbprm.algo & (BE_LB_KIND | BE_LB_PARM)) == (BE_LB_KIND_HI | BE_LB_HASH_PRM))
		s->txn.req.flags |= HTTP_MSGF_WAIT_CONN;

	if (be->options2 & PR_O2_NODELAY) {
		s->req->flags |= CF_NEVER_WAIT;
		s->rep->flags |= CF_NEVER_WAIT;
	}


	s->req->analysers |= be->be_req_ana & ~(s->listener->analysers);

	return 1;
}
