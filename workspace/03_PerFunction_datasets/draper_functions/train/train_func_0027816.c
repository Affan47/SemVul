RFC2616_Body(const struct sess *sp)
{
	struct http *hp;
	char *b;

	hp = sp->wrk->beresp;

	if (hp->protover < 1.1 && !http_HdrIs(hp, H_Connection, "keep-alive"))
		sp->wrk->do_close = 1;
	else if (http_HdrIs(hp, H_Connection, "close"))
		sp->wrk->do_close = 1;
	else
		sp->wrk->do_close = 0;

	if (!strcasecmp(http_GetReq(sp->wrk->bereq), "head")) {


		sp->wrk->stats.fetch_head++;
		return (BS_NONE);
	}

	if (hp->status <= 199) {


		sp->wrk->stats.fetch_1xx++;
		return (BS_NONE);
	}

	if (hp->status == 204) {


		sp->wrk->stats.fetch_204++;
		return (BS_NONE);
	}

	if (hp->status == 304) {


		sp->wrk->stats.fetch_304++;
		return (BS_NONE);
	}

	if (http_HdrIs(hp, H_Transfer_Encoding, "chunked")) {
		 sp->wrk->stats.fetch_chunked++;
		return (BS_CHUNKED);
	}

	if (http_GetHdr(hp, H_Transfer_Encoding, &b)) {
		sp->wrk->stats.fetch_bad++;
		return (BS_ERROR);
	}

	if (http_GetHdr(hp, H_Content_Length, &sp->wrk->h_content_length)) {
		sp->wrk->stats.fetch_length++;
		return (BS_LENGTH);
	}

	if (http_HdrIs(hp, H_Connection, "keep-alive")) {


		sp->wrk->stats.fetch_zero++;
		return (BS_ZERO);
	}

	if (http_HdrIs(hp, H_Connection, "close")) {


		sp->wrk->stats.fetch_close++;
		return (BS_EOF);
	}

	if (hp->protover < 1.1) {


		sp->wrk->stats.fetch_oldhttp++;
		return (BS_EOF);
	}


	sp->wrk->stats.fetch_eof++;
	return (BS_EOF);
}
