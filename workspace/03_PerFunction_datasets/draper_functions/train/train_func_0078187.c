deinit_fromutf7(void *ptr, int *errptr)
{
	struct libmail_u_convert_fromimaputf7 *fromutf7=
		(struct libmail_u_convert_fromimaputf7 *)ptr;
	int rc;

	if (fromutf7->seenamp || fromutf7->inmod)
	{
		if (fromutf7->errflag == 0)
		{
			fromutf7->errflag= -1;
			errno=EILSEQ;
		}
	}

	if (fromutf7->convbuf_cnt)
		convert_fromutf7_flush(fromutf7);

	rc=fromutf7->hdr.next->deinit_handler(fromutf7->hdr.next->ptr, errptr);

	if (fromutf7->errflag && rc == 0)
		rc=fromutf7->errflag;

	if (errptr && fromutf7->converr)
		*errptr=1;

	free(fromutf7);
	return rc;
}
