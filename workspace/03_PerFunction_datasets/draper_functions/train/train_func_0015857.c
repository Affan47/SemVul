cnt_start(struct sess *sp, struct worker *wrk, struct req *req)
{
	uint16_t done;
	char *p;
	const char *r = "HTTP/1.1 100 Continue\r\n\r\n";

	CHECK_OBJ_NOTNULL(sp, SESS_MAGIC);
	CHECK_OBJ_NOTNULL(wrk, WORKER_MAGIC);
	CHECK_OBJ_NOTNULL(req, REQ_MAGIC);
	AZ(req->restarts);
	AZ(req->obj);
	AZ(req->vcl);
	EXP_Clr(&req->exp);
	AZ(req->esi_level);


	wrk->stats.client_req++;
	assert(!isnan(sp->t_req));
	wrk->acct_tmp.req++;


	req->xid = ++xids;
	WSP(sp, SLT_ReqStart, "%s %s %u", sp->addr, sp->port,  req->xid);


	VCL_Refresh(&wrk->vcl);
	req->vcl = wrk->vcl;
	wrk->vcl = NULL;

	http_Setup(req->http, req->ws);
	done = http_DissectRequest(sp);


	if (done == 400) {
		sp->step = STP_DONE;
		SES_Close(sp, "junk");
		return (0);
	}


	req->ws_req = WS_Snapshot(req->ws);


	HTTP_Copy(req->http0, req->http);

	if (done != 0) {
		req->err_code = done;
		sp->step = STP_ERROR;
		return (0);
	}

	req->doclose = http_DoConnection(req->http);


	if (http_GetHdr(req->http, H_Expect, &p)) {
		if (strcasecmp(p, "100-continue")) {
			req->err_code = 417;
			sp->step = STP_ERROR;
			return (0);
		}


		(void)write(sp->fd, r, strlen(r));


		http_Unset(req->http, H_Expect);
	}

	sp->step = STP_RECV;
	return (0);
}
