auth(int so, struct group *group, struct request* rq, int *flags) {
char	*authorization = NULL;

    my_xlog(LOG_NOTICE|LOG_DBG|LOG_INFORM, "auth(): Authenticate request.\n");

    if ( !authreq ) {
	my_xlog(LOG_NOTICE|LOG_DBG|LOG_INFORM, "auth(): Something wrong with passwd_file module.\n");
	return(MOD_CODE_OK);
    }

    WRLOCK_PWF_CONFIG ;
    check_pwf_age();
    check_pwf_template_age();
    UNLOCK_PWF_CONFIG;

    RDLOCK_PWF_CONFIG ;
    if ( !pwds ) {
	my_xlog(LOG_SEVERE, "auth(): Passwd file was not loaded.\n");
	UNLOCK_PWF_CONFIG ;
	return(MOD_CODE_OK);
    }
    if ( rq->av_pairs)
	authorization = attr_value(rq->av_pairs, "Proxy-Authorization");
    if ( !authorization ) {

	send_auth_req(so, rq);
	SET(*flags, MOD_AFLAG_OUT);
	UNLOCK_PWF_CONFIG ;
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
    UNLOCK_PWF_CONFIG ;
    return(MOD_CODE_OK);
}
