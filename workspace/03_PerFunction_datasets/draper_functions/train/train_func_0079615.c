sasl_user_exists(sasl_conn_t *conn,
		     const char *service,
		     const char *user_realm,
		     const char *user)
{
    int result=SASL_NOMECH;
    const char *mlist = NULL, *mech = NULL;
    void *context;
    sasl_getopt_t *getopt;
    struct sasl_verify_password_s *v;


    if (_sasl_server_active==0) return SASL_NOTINIT;
    if (!conn) return SASL_BADPARAM;
    if (!user || conn->type != SASL_CONN_SERVER)
	PARAMERROR(conn);

    if(!service) service = conn->service;


    if (_sasl_getcallback(conn, SASL_CB_GETOPT, (sasl_callback_ft *)&getopt, &context)
            == SASL_OK) {
        getopt(context, NULL, "pwcheck_method", &mlist, NULL);
    }

    if(!mlist) mlist = DEFAULT_CHECKPASS_MECH;

    result = SASL_NOMECH;

    mech = mlist;
    while (*mech && result != SASL_OK) {
	for (v = _sasl_verify_password; v->name; v++) {
	    if(is_mech(mech, v->name)) {
		result = v->verify(conn, user, NULL, service, user_realm);
		break;
	    }
	}
	if (result != SASL_OK) {

	    while (*mech && !isspace((int) *mech)) mech++;
	    while (*mech && isspace((int) *mech)) mech++;
	}
    }


    if (result == SASL_BADPARAM) {
	result = SASL_OK;
    }

    if (result == SASL_NOMECH) {

	_sasl_log(conn, SASL_LOG_ERR, "no plaintext password verifier?");
	sasl_seterror(conn, SASL_NOLOG, "no plaintext password verifier?");
    }

    RETURN(conn, result);
}
