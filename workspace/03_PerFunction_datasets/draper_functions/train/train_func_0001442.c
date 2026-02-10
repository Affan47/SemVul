ssl3_NewSessionID(sslSocket *ss, PRBool is_server)
{
    sslSessionID *sid;

    sid = PORT_ZNew(sslSessionID);
    if (sid == NULL)
    	return sid;

    if (is_server) {
        const SECItem *  srvName;
        SECStatus        rv = SECSuccess;

        ssl_GetSpecReadLock(ss);
        srvName = &ss->ssl3.prSpec->srvVirtName;
        if (srvName->len && srvName->data) {
            rv = SECITEM_CopyItem(NULL, &sid->u.ssl3.srvName, srvName);
        }
        ssl_ReleaseSpecReadLock(ss);
        if (rv != SECSuccess) {
            PORT_Free(sid);
            return NULL;
        }
    }
    sid->peerID		= (ss->peerID == NULL) ? NULL : PORT_Strdup(ss->peerID);
    sid->urlSvrName	= (ss->url    == NULL) ? NULL : PORT_Strdup(ss->url);
    sid->addr           = ss->sec.ci.peer;
    sid->port           = ss->sec.ci.port;
    sid->references     = 1;
    sid->cached         = never_cached;
    sid->version        = ss->version;

    sid->u.ssl3.keys.resumable = PR_TRUE;
    sid->u.ssl3.policy         = SSL_ALLOWED;
    sid->u.ssl3.clientWriteKey = NULL;
    sid->u.ssl3.serverWriteKey = NULL;

    if (is_server) {
	SECStatus rv;
	int       pid = SSL_GETPID();

	sid->u.ssl3.sessionIDLength = SSL3_SESSIONID_BYTES;
	sid->u.ssl3.sessionID[0]    = (pid >> 8) & 0xff;
	sid->u.ssl3.sessionID[1]    =  pid       & 0xff;
	rv = PK11_GenerateRandom(sid->u.ssl3.sessionID + 2,
	                         SSL3_SESSIONID_BYTES -2);
	if (rv != SECSuccess) {
	    ssl_FreeSID(sid);
	    ssl_MapLowLevelError(SSL_ERROR_GENERATE_RANDOM_FAILURE);
	    return NULL;
    	}
    }
    return sid;
}
