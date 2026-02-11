sess_prepare_conn_req(struct session *s, struct stream_interface *si) {
	DPRINTF(stderr,"[%u] %s: sess=%p rq=%p, rp=%p, exp(r,w)=%u,%u rqf=%08x rpf=%08x rql=%d rpl=%d cs=%d ss=%d\n",
		now_ms, __FUNCTION__,
		s,
		s->req, s->rep,
		s->req->rex, s->rep->wex,
		s->req->flags, s->rep->flags,
		s->req->l, s->rep->l, s->rep->cons->state, s->req->cons->state);

	if (si->state != SI_ST_REQ)
		return;


	if (srv_redispatch_connect(s) != 0) {


		if (si->state == SI_ST_QUE)
			return;


		si->shutr(si);
		si->shutw(si);
		si->ob->flags |= BF_WRITE_ERROR;
		if (!si->err_type)
			si->err_type = SI_ET_CONN_OTHER;
		si->state = SI_ST_CLO;
		if (s->srv_error)
			s->srv_error(s, si);
		return;
	}


	s->logs.t_queue = tv_ms_elapsed(&s->logs.tv_accept, &now);
	si->state = SI_ST_ASS;
}
