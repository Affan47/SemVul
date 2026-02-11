FetchReqBody(struct sess *sp)
{
	unsigned long content_length;
	char buf[8192];
	char *ptr, *endp;
	int rdcnt;

	if (http_GetHdr(sp->http, H_Content_Length, &ptr)) {

		content_length = strtoul(ptr, &endp, 10);

		while (content_length) {
			if (content_length > sizeof buf)
				rdcnt = sizeof buf;
			else
				rdcnt = content_length;
			rdcnt = HTC_Read(sp->htc, buf, rdcnt);
			if (rdcnt <= 0)
				return (1);
			content_length -= rdcnt;
			if (!sp->sendbody)
				continue;
			(void)WRW_Write(sp->wrk, buf, rdcnt);
			if (WRW_Flush(sp->wrk))
				return (2);
		}
	}
	if (http_GetHdr(sp->http, H_Transfer_Encoding, NULL)) {

		WSL(sp->wrk, SLT_Debug, sp->fd, "Transfer-Encoding in request");
		return (1);
	}
	return (0);
}
