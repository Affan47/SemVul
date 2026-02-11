httpFixupAuthentication(request_t * request, request_t * orig_request, const HttpHeader * hdr_in, HttpHeader * hdr_out, http_state_flags flags)
{
    http_hdr_type header = flags.originpeer ? HDR_AUTHORIZATION : HDR_PROXY_AUTHORIZATION;


    if (!request->flags.proxying)
	return;


    if (!orig_request->peer_login)
	return;


    if (httpHeaderHas(hdr_out, header))
	return;


    if (flags.originpeer && strcmp(orig_request->peer_login, "PROXYPASS") == 0 && httpHeaderHas(hdr_in, HDR_PROXY_AUTHORIZATION)) {
	const char *auth = httpHeaderGetStr(hdr_in, HDR_PROXY_AUTHORIZATION);
	if (auth && strncasecmp(auth, "basic ", 6) == 0) {
	    httpHeaderPutStr(hdr_out, header, auth);
	    return;
	}
    }

    if (*orig_request->peer_login == '*') {
	char loginbuf[256];
	const char *username = "-";
	if (orig_request->extacl_user)
	    username = orig_request->extacl_user;
	else if (orig_request->auth_user_request)
	    username = authenticateUserRequestUsername(orig_request->auth_user_request);
	snprintf(loginbuf, sizeof(loginbuf), "%s%s", username, orig_request->peer_login + 1);
	httpHeaderPutStrf(hdr_out, header, "Basic %s", base64_encode(loginbuf));
	return;
    }

    if (orig_request->extacl_user && orig_request->extacl_passwd &&
	(strcmp(orig_request->peer_login, "PASS") == 0 || strcmp(orig_request->peer_login, "PROXYPASS") == 0)) {
	char loginbuf[256];
	snprintf(loginbuf, sizeof(loginbuf), "%s:%s", orig_request->extacl_user, orig_request->extacl_passwd);
	httpHeaderPutStrf(hdr_out, header, "Basic %s",
	    base64_encode(loginbuf));
	return;
    }
#if HAVE_KRB5 && HAVE_GSSAPI

    if (strcmp(orig_request->peer_login, "NEGOTIATE") == 0) {
	char *Token;
	Token = peer_proxy_negotiate_auth(NULL, request->peer_host);
	if (Token) {
	    httpHeaderPutStrf(hdr_out, header, "Negotiate %s", Token);
	}
	return;
    }
#endif

    httpHeaderPutStrf(hdr_out, header, "Basic %s", base64_encode(orig_request->peer_login));
    return;
}
