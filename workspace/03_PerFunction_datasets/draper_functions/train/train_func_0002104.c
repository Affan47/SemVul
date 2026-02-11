res_dorange(struct sess *sp, const char *r, ssize_t *plow, ssize_t *phigh)
{
	ssize_t low, high, has_low;

	(void)sp;
	if (strncmp(r, "bytes=", 6))
		return;
	r += 6;


	has_low = low = 0;
	if (!vct_isdigit(*r) && *r != '-')
		return;
	while (vct_isdigit(*r)) {
		has_low = 1;
		low *= 10;
		low += *r - '0';
		r++;
	}

	if (low >= sp->obj->len)
		return;

	if (*r != '-')
		return;
	r++;


	if (vct_isdigit(*r)) {
		high = 0;
		while (vct_isdigit(*r)) {
			high *= 10;
			high += *r - '0';
			r++;
		}
		if (!has_low) {
			low = sp->obj->len - high;
			high = sp->obj->len - 1;
		}
	} else
		high = sp->obj->len - 1;
	if (*r != '\0')
		return;

	if (high >= sp->obj->len)
		high = sp->obj->len - 1;

	if (low > high)
		return;

	http_PrintfHeader(sp->wrk, sp->fd, sp->wrk->resp,
	    "Content-Range: bytes %jd-%jd/%jd",
	    (intmax_t)low, (intmax_t)high, (intmax_t)sp->obj->len);
	http_Unset(sp->wrk->resp, H_Content_Length);
	assert(sp->wrk->res_mode & RES_LEN);
	http_PrintfHeader(sp->wrk, sp->fd, sp->wrk->resp,
	    "Content-Length: %jd", (intmax_t)(1 + high - low));
	http_SetResp(sp->wrk->resp, "HTTP/1.1", 206, "Partial Content");

	*plow = low;
	*phigh = high;
}
