__ncp_abort_request(struct ncp_server *server, struct ncp_request_reply *req, int err)
{

	switch (req->status) {
		case RQ_IDLE:
		case RQ_DONE:
			break;
		case RQ_QUEUED:
			list_del_init(&req->req);
			ncp_finish_request(server, req, err);
			break;
		case RQ_INPROGRESS:
			req->status = RQ_ABANDONED;
			break;
		case RQ_ABANDONED:
			break;
	}
}
