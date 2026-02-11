RES_WriteObj(struct sess *sp)
{
	char *r;
	ssize_t low, high;

	CHECK_OBJ_NOTNULL(sp, SESS_MAGIC);

	WRW_Reserve(sp->wrk, &sp->fd);

	if (sp->req->obj->response == 200 &&
	    sp->req->http->conds &&
	    RFC2616_Do_Cond(sp)) {
		sp->req->wantbody = 0;
		http_SetResp(sp->req->resp, "HTTP/1.1", 304, "Not Modified");
		http_Unset(sp->req->resp, H_Content_Length);
		http_Unset(sp->req->resp, H_Transfer_Encoding);
	}


	low = 0;
	high = sp->req->obj->len - 1;
	if (
	    sp->req->wantbody &&
	    (sp->wrk->res_mode & RES_LEN) &&
	    !(sp->wrk->res_mode & (RES_ESI|RES_ESI_CHILD|RES_GUNZIP)) &&
	    cache_param->http_range_support &&
	    sp->req->obj->response == 200 &&
	    http_GetHdr(sp->req->http, H_Range, &r))
		res_dorange(sp, r, &low, &high);


	if (sp->wrk->res_mode & RES_GUNZIP)
		http_Unset(sp->req->resp, H_Content_Encoding);


	if (!(sp->wrk->res_mode & RES_ESI_CHILD))
		sp->wrk->acct_tmp.hdrbytes +=
		    http_Write(sp->wrk, sp->vsl_id, sp->req->resp, 1);

	if (!sp->req->wantbody)
		sp->wrk->res_mode &= ~RES_CHUNKED;

	if (sp->wrk->res_mode & RES_CHUNKED)
		WRW_Chunked(sp->wrk);

	if (!sp->req->wantbody) {

	} else if (sp->req->obj->len == 0) {

	} else if (sp->wrk->res_mode & RES_ESI) {
		ESI_Deliver(sp);
	} else if (sp->wrk->res_mode & RES_ESI_CHILD && sp->req->gzip_resp) {
		ESI_DeliverChild(sp);
	} else if (sp->wrk->res_mode & RES_ESI_CHILD &&
	    !sp->req->gzip_resp && sp->req->obj->gziped) {
		res_WriteGunzipObj(sp);
	} else if (sp->wrk->res_mode & RES_GUNZIP) {
		res_WriteGunzipObj(sp);
	} else {
		res_WriteDirObj(sp, low, high);
	}

	if (sp->wrk->res_mode & RES_CHUNKED &&
	    !(sp->wrk->res_mode & RES_ESI_CHILD))
		WRW_EndChunk(sp->wrk);

	if (WRW_FlushRelease(sp->wrk) && sp->fd >= 0)
		SES_Close(sp, "remote closed");
}
