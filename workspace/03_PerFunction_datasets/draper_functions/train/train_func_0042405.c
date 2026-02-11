gfarm_auth_sharedsecret_response(struct gfp_xdr *conn, struct passwd *pwd)
{
	gfarm_error_t e;
	gfarm_uint32_t request;
	gfarm_int32_t error = GFARM_AUTH_ERROR_EXPIRED;
	int eof, try = 0;


	for (;;) {
		++try;
		e = gfp_xdr_recv(conn, 0, &eof, "i", &request);
		if (e != GFARM_ERR_NO_ERROR) {
			gflog_error(GFARM_MSG_1000034,
			    "auth_sharedsecret_response: %s",
			    gfarm_error_string(e));
			return (e);
		}
		if (eof) {
			gflog_error(GFARM_MSG_1000035,
			    "auth_sharedsecret_response: "
			    "unexpected EOF");
			return (GFARM_ERR_PROTOCOL);
		}
		switch (request) {
		case GFARM_AUTH_SHAREDSECRET_MD5:
		case GFARM_AUTH_SHAREDSECRET_GIVEUP:
			e = gfp_xdr_send(conn, "i", GFARM_AUTH_ERROR_NO_ERROR);
			break;
		default:
			error = GFARM_AUTH_ERROR_NOT_SUPPORTED;
			e = gfp_xdr_send(conn, "i", error);
			break;
		}
		if (e != GFARM_ERR_NO_ERROR) {
			gflog_error(GFARM_MSG_1000036,
			    "auth_sharedsecret: key query: %s",
			    gfarm_error_string(e));
			return (e);
		}
		switch (request) {
		case GFARM_AUTH_SHAREDSECRET_GIVEUP:
			return (gfarm_auth_sharedsecret_giveup_response(
					conn, try, error));
		case GFARM_AUTH_SHAREDSECRET_MD5:
			e = gfarm_auth_sharedsecret_md5_response(
				conn, pwd, &error);
			if (e != GFARM_ERRMSG_AUTH_SHAREDSECRET_MD5_CONTINUE)
				return (e);
		default:
			e = gfp_xdr_flush(conn);
			if (e != GFARM_ERR_NO_ERROR) {
				gflog_error(GFARM_MSG_1000037,
				    "auth_sharedsecret: request "
				    "response: %s", gfarm_error_string(e));
				return (e);
			}
			break;
		}
	}
}
