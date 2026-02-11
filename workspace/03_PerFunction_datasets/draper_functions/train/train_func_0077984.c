tds_goodread(TDSSOCKET * tds, unsigned char *buf, int buflen, unsigned char unfinished)
{
	int rc, got = 0;

	if (tds == NULL || buf == NULL || buflen < 1)
		return -1;

	for (;;) {
		int len;

		if (IS_TDSDEAD(tds))
			return -1;

		if ((len = tds_select(tds, TDSSELREAD, tds->query_timeout)) > 0) {

			len = READSOCKET(tds->s, buf + got, buflen);

			if (len < 0 && TDSSOCK_WOULDBLOCK(sock_errno))
				continue;

			if (len <= 0) {
				tdserror(tds->tds_ctx, tds, len == 0 ? TDSESEOF : TDSEREAD, sock_errno);
				tds_close_socket(tds);
				return -1;
			}
		} else if (len < 0) {
			if (TDSSOCK_WOULDBLOCK(sock_errno))
				continue;
			tdserror(tds->tds_ctx, tds, TDSEREAD, sock_errno);
			tds_close_socket(tds);
			return -1;
		} else {
			switch (rc = tdserror(tds->tds_ctx, tds, TDSETIME, sock_errno)) {
			case TDS_INT_CONTINUE:
				continue;
			case TDS_INT_TIMEOUT:
				tds_send_cancel(tds);
				continue;
			default:
			case TDS_INT_CANCEL:
				tds_close_socket(tds);
				return -1;
			}
			assert(0);
		}

		got += len;
		buflen -= len;

		if (buflen <= 0)
			break;

		if (unfinished && got)
			break;
	}
	return got;
}
