getntype(int4 node_type, int4 type_mask)
{
	struct rreq	*request;
	struct rreply	*reply;
	struct nmsg	nhreq;
	struct nmsg	nhreply;

	LAM_ZERO_ME(nhreq);
	LAM_ZERO_ME(nhreply);


	request = (struct rreq *) nhreq.nh_data;
	request->rq_src_event = -lam_getpid();
	request->rq_request = RQGETNTYPE;
	request->rq_nodetype = node_type;
	request->rq_typemask = type_mask;

	nhreq.nh_dl_event = EVROUTER;
	nhreq.nh_node = LOCAL;
	nhreq.nh_event = EVROUTER;
	nhreq.nh_type = RSMART;
	nhreq.nh_flags = 0;
	nhreq.nh_length = 0;
	nhreq.nh_msg = 0;

	nhreply.nh_event = -lam_getpid();
	nhreply.nh_type = 0;
	nhreply.nh_flags = 0;
	nhreply.nh_length = 0;
	nhreply.nh_msg = 0;

	if (dsfr(&nhreq, &nhreply)) {
		return(ERROR);
	}

	reply = (struct rreply *) nhreply.nh_data;

	if (reply->rr_reply) {
		errno = reply->rr_reply;
		return(ERROR);
	} else {
		return(reply->rr_ntype);
	}
}
