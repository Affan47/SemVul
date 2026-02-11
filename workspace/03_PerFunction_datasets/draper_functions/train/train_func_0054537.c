auth(int so, struct group *group, struct request* rq, int *flags) {
char	*authorization = NULL;

    my_xlog(OOPS_LOG_NOTICE|OOPS_LOG_DBG|OOPS_LOG_INFORM, "auth(): Authenticate request.\n");

    if ( !authreq ) {
	my_xlog(OOPS_LOG_NOTICE|OOPS_LOG_DBG|OOPS_LOG_INFORM, "auth(): Something wrong with pam module.\n");
	return(MOD_CODE_OK);
    }


    if ( rq->av_pairs)
	authorization = attr_value(rq->av_pairs, "Proxy-Authorization");
    if ( !authorization ) {

	send_auth_req(so, rq);
	SET(*flags, MOD_AFLAG_OUT);

	return(MOD_CODE_ERR);
    } else {
	char *data;
	if ( !strncasecmp(authorization, "Basic", 5 ) ) {
	  int	 rc;
	  char	*up=NULL, *u, *p;
	    data = authorization + 5;
	    while ( *data && IS_SPACE(*data) ) data++;
	    if ( *data ) up = base64_decode(data);
	    if ( up ) {

		u = up;
		p = strchr(up, ':');
		if ( p ) { *p=0; p++; }
		rc = pwf_auth(u, p);

		my_xlog(OOPS_LOG_NOTICE|OOPS_LOG_DBG|OOPS_LOG_INFORM, "auth(): rc=%d\n",rc);

	        if ( rc ) {

		    free(up);
		    goto au_f;
		  } else {
		    IF_STRDUP(rq->proxy_user, u);
		    free(up);
		    goto au_ok;
		  }
	    }
	} else {

	    if ( badsch ) {
		writet(so, badsch, badschlen, 30);
		SET(*flags, MOD_AFLAG_OUT);
	    }
	    UNLOCK_PWF_CONFIG ;
	    return(MOD_CODE_ERR);
	}
au_f:   send_auth_req(so, rq);
	SET(*flags, MOD_AFLAG_OUT);
	UNLOCK_PWF_CONFIG ;
	return(MOD_CODE_ERR);
    }
au_ok:
    SET(*flags, MOD_AFLAG_CKACC);
    UNLOCK_PWF_CONFIG ;
    return(MOD_CODE_OK);
}
