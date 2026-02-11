cnt_streambody(struct sess *sp)
{
	int i;
	struct stream_ctx sctx;
	uint8_t obuf[sp->wrk->res_mode & RES_GUNZIP ?
	    params->gzip_stack_buffer : 1];

	memset(&sctx, 0, sizeof sctx);
	sctx.magic = STREAM_CTX_MAGIC;
	AZ(sp->wrk->sctx);
	sp->wrk->sctx = &sctx;

	if (sp->wrk->res_mode & RES_GUNZIP) {
		sctx.vgz = VGZ_NewUngzip(sp, "U S -");
		sctx.obuf = obuf;
		sctx.obuf_len = sizeof (obuf);
	}

	RES_StreamStart(sp);

	i = FetchBody(sp);

	sp->wrk->h_content_length = NULL;

	http_Setup(sp->wrk->bereq, NULL);
	http_Setup(sp->wrk->beresp, NULL);
	sp->wrk->vfp = NULL;
	AZ(sp->vbc);
	AN(sp->director);

	if (!i && sp->obj->objcore != NULL) {
		EXP_Insert(sp->obj);
		AN(sp->obj->objcore);
		AN(sp->obj->objcore->ban);
		HSH_Unbusy(sp);
	} else {
		sp->doclose = "Stream error";
	}
	sp->acct_tmp.fetch++;
	sp->director = NULL;
	sp->restarts = 0;

	RES_StreamEnd(sp);
	if (sp->wrk->res_mode & RES_GUNZIP)
		VGZ_Destroy(&sctx.vgz);

	sp->wrk->sctx = NULL;
	assert(WRW_IsReleased(sp->wrk));
	assert(sp->wrk->wrw.ciov == sp->wrk->wrw.siov);
	(void)HSH_Deref(sp->wrk, NULL, &sp->obj);
	http_Setup(sp->wrk->resp, NULL);
	sp->step = STP_DONE;
	return (0);
}
