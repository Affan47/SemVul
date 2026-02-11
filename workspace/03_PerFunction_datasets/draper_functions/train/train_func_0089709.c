ved_include(struct sess *sp, const char *src, const char *host)
{
	struct object *obj;
	struct worker *w;
	char *sp_ws_wm;
	char *wrk_ws_wm;
	unsigned sxid, res_mode;

	w = sp->wrk;

	if (sp->esi_level >= cache_param->max_esi_depth)
		return;
	sp->esi_level++;

	(void)WRW_FlushRelease(w);

	obj = sp->wrk->obj;
	sp->wrk->obj = NULL;
	res_mode = sp->wrk->res_mode;


	HTTP_Copy(sp->http, sp->http0);


	sp_ws_wm = WS_Snapshot(sp->ws);
	wrk_ws_wm = WS_Snapshot(w->ws);

	http_SetH(sp->http, HTTP_HDR_URL, src);
	if (host != NULL && *host != '\0')  {
		http_Unset(sp->http, H_Host);
		http_Unset(sp->http, H_If_Modified_Since);
		http_SetHeader(w, sp->vsl_id, sp->http, host);
	}


	sp->director = NULL;
	sp->step = STP_RECV;
	http_ForceGet(sp->http);


	sp->http->conds = 0;
	http_Unset(sp->http, H_If_Modified_Since);


	http_Unset(sp->http, H_Content_Length);

	sxid = sp->xid;
	while (1) {
		sp->wrk = w;
		CNT_Session(sp);
		if (sp->step == STP_DONE)
			break;
		AZ(sp->wrk);
		WSL_Flush(w, 0);
		DSL(0x20, SLT_Debug, sp->vsl_id, "loop waiting for ESI");
		(void)usleep(10000);
	}
	sp->xid = sxid;
	AN(sp->wrk);
	assert(sp->step == STP_DONE);
	sp->esi_level--;
	sp->wrk->obj = obj;
	sp->wrk->res_mode = res_mode;


	WS_Reset(sp->ws, sp_ws_wm);
	WS_Reset(w->ws, wrk_ws_wm);

	WRW_Reserve(sp->wrk, &sp->fd);
	if (sp->wrk->res_mode & RES_CHUNKED)
		WRW_Chunked(sp->wrk);
}
