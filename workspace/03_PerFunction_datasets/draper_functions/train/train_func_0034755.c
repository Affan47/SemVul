authenticateFixHeader(HttpReply * rep, auth_user_request_t * auth_user_request, request_t * request, int accelerated, int internal)

{
    int type = 0;
    switch (rep->sline.status) {
    case HTTP_PROXY_AUTHENTICATION_REQUIRED:

	type = HDR_PROXY_AUTHENTICATE;
	break;
    case HTTP_UNAUTHORIZED:

	type = HDR_WWW_AUTHENTICATE;
	break;
    default:


	break;
    }
    debug(29, 9) ("authenticateFixHeader: headertype:%d authuser:%p\n", type, auth_user_request);
    if (((rep->sline.status == HTTP_PROXY_AUTHENTICATION_REQUIRED)
	    || (rep->sline.status == HTTP_UNAUTHORIZED)) && internal)

    {
	if ((auth_user_request != NULL) && (auth_user_request->auth_user->auth_module > 0) && authenticateDirection(auth_user_request) == 1)
	    authscheme_list[auth_user_request->auth_user->auth_module - 1].authFixHeader(auth_user_request, rep, type, request);
	else {
	    int i;
	    authScheme *scheme;

	    for (i = 0; i < Config.authConfig.n_configured; i++) {
		scheme = Config.authConfig.schemes + i;
		if (authscheme_list[scheme->Id].Active()) {
		    if (auth_user_request && scheme->Id == auth_user_request->auth_user->auth_module - 1)
			authscheme_list[scheme->Id].authFixHeader(
			    auth_user_request, rep, type, request);
		    else
			authscheme_list[scheme->Id].authFixHeader(
			    NULL, rep, type, request);
		} else {
		    debug(29, 4) ("authenticateFixHeader: Configured scheme %s not Active\n", scheme->typestr);
		}
	    }
	}
    }


    if ((auth_user_request != NULL) && (auth_user_request->auth_user->auth_module > 0)
	&& (authscheme_list[auth_user_request->auth_user->auth_module - 1].AddHeader))
	authscheme_list[auth_user_request->auth_user->auth_module - 1].AddHeader(auth_user_request, rep, accelerated);
    if (auth_user_request != NULL && auth_user_request->lastReply != AUTH_AUTHENTICATED)
	auth_user_request->lastReply = AUTH_ACL_CANNOT_AUTHENTICATE;
}
