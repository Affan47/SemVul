RES_WriteObj(struct sess *sp)
{
	char *r;
	ssize_t low, high;

	CHECK_OBJ_NOTNULL(sp, SESS_MAGIC);

	WRW_Reserve(sp->wrk, &sp->fd);


	low = 0;
	high = sp->obj->len - 1;
	if (!(sp->wrk->res_mode & (RES_ESI|RES_ESI_CHILD|RES_GUNZIP)) &&
	    params->http_range_support && sp->obj->response == 200 &&
	    sp->wantbody && http_GetHdr(sp->http, H_Range, &r))
		res_dorange(sp, r, &low, &high);


	if (sp->wrk->res_mode & RES_GUNZIP)
		http_Unset(sp->wrk->resp, H_Content_Encoding);


	if (!(sp->wrk->res_mode & RES_ESI_CHILD))
		sp->acct_tmp.hdrbytes +=
		    http_Write(sp->wrk, sp->wrk->resp, 1);

	if (sp->wrk->res_mode & RES_CHUNKED)
		WRW_Chunked(sp->wrk);

	if (!sp->wantbody) {

	} else if (sp->obj->len == 0) {

	} else if (sp->wrk->res_mode & RES_ESI) {
		ESI_Deliver(sp);
	} else if (sp->wrk->res_mode & RES_ESI_CHILD && sp->wrk->gzip_resp) {
		ESI_DeliverChild(sp);
	} else if (sp->wrk->res_mode & RES_GUNZIP) {
		res_WriteGunzipObj(sp);
	} else {
		res_WriteDirObj(sp, low, high);
	}

	if (sp->wrk->res_mode & RES_CHUNKED &&
	    !(sp->wrk->res_mode & RES_ESI_CHILD))
		WRW_EndChunk(sp->wrk);

	if (WRW_FlushRelease(sp->wrk))
		vca_close_session(sp, "remote closed");
}
