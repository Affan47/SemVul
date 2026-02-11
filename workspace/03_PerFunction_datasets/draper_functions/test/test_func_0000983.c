imap_sendAuthenticate(connection_t *cxn)
{
    conn_ret result;
    char *p;

#ifdef HAVE_SASL
    const char *mechusing;
    int saslresult=SASL_NOMECH;

    sasl_interact_t *client_interact=NULL;

    if (cxn->imap_capabilities->saslmechs) {
	saslresult=sasl_client_start(cxn->imap_saslconn,
				     cxn->imap_capabilities->saslmechs,
				     &client_interact,
				     NULL, NULL,
				     &mechusing);
    }


    if (saslresult == SASL_NOMECH)
    {

#else

     {

#endif
	d_printf(1,"%s:%d:IMAP No mechanism found. Trying login method\n",
		 hostPeerName (cxn->myHost), cxn->ident) ;

	if (cxn->imap_capabilities->logindisabled==1)
	{
	    d_printf(0,"%s:%d:IMAP Login command w/o security layer not allowed on this server\n",
		     hostPeerName (cxn->myHost), cxn->ident);
	    return RET_FAIL;
	}

	if (deliver_authname==NULL)
	{
	    d_printf(0,"%s:%d:IMAP Unable to log in because can't find a authname\n",
		     hostPeerName (cxn->myHost), cxn->ident) ;
	    return RET_FAIL;
	}

	if (deliver_password==NULL)
	{
	    d_printf(0,"%s:%d:IMAP Unable to log in because can't find a password\n",
		     hostPeerName (cxn->myHost), cxn->ident) ;
	    return RET_FAIL;
	}

	imap_GetTag(cxn);

        p = concat(cxn->imap_currentTag, " LOGIN ", deliver_authname, " \"",
                   deliver_password, "\"\r\n", (char *) 0);

	result = WriteToWire_imapstr(cxn, p, strlen(p));
        if (result != RET_OK)
            return result;

        cxn->imap_state = IMAP_WRITING_STARTAUTH;

	return RET_OK;
    }

#ifdef HAVE_SASL
    if ((saslresult != SASL_OK) &&
	(saslresult != SASL_CONTINUE)) {

	d_printf(0,"%s:%d:IMAP Error calling sasl_client_start (%s) mechusing = %s\n",
		 hostPeerName (cxn->myHost), cxn->ident,
		 sasl_errstring(saslresult, NULL, NULL), mechusing);
	return RET_FAIL;
    }

    d_printf(1,"%s:%d:IMAP Trying to authenticate to imap with %s mechanism\n",
	     hostPeerName (cxn->myHost), cxn->ident,
	     mechusing);

    imap_GetTag(cxn);

    p = concat(cxn->imap_currentTag, " AUTHENTICATE ", mechusing, "\r\n",
               (char *) 0);
    result = WriteToWire_imapstr(cxn, p, strlen(p));
    if (result != RET_OK)
        return result;

    cxn->imap_state = IMAP_WRITING_STARTAUTH;

    return RET_OK;
#endif
}
