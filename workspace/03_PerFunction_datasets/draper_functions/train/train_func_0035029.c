CacheSID(sslSessionID *sid)
{
    PRUint32  expirationPeriod;

    PORT_Assert(sid->cached == never_cached);

    SSL_TRC(8, ("SSL: Cache: sid=0x%x cached=%d addr=0x%08x%08x%08x%08x port=0x%04x "
		"time=%x cached=%d",
		sid, sid->cached, sid->addr.pr_s6_addr32[0],
		sid->addr.pr_s6_addr32[1], sid->addr.pr_s6_addr32[2],
		sid->addr.pr_s6_addr32[3],  sid->port, sid->creationTime,
		sid->cached));

    if (!sid->urlSvrName) {

        return;
    }


    if (sid->version < SSL_LIBRARY_VERSION_3_0) {
	expirationPeriod = ssl_sid_timeout;
	PRINT_BUF(8, (0, "sessionID:",
		  sid->u.ssl2.sessionID, sizeof(sid->u.ssl2.sessionID)));
	PRINT_BUF(8, (0, "masterKey:",
		  sid->u.ssl2.masterKey.data, sid->u.ssl2.masterKey.len));
	PRINT_BUF(8, (0, "cipherArg:",
		  sid->u.ssl2.cipherArg.data, sid->u.ssl2.cipherArg.len));
    } else {
	if (sid->u.ssl3.sessionIDLength == 0 &&
	    sid->u.ssl3.locked.sessionTicket.ticket.data == NULL)
	    return;


	if (sid->u.ssl3.sessionIDLength == 0) {
	    SECStatus rv;
	    rv = PK11_GenerateRandom(sid->u.ssl3.sessionID,
		SSL3_SESSIONID_BYTES);
	    if (rv != SECSuccess)
		return;
	    sid->u.ssl3.sessionIDLength = SSL3_SESSIONID_BYTES;
	}
	expirationPeriod = ssl3_sid_timeout;
	PRINT_BUF(8, (0, "sessionID:",
		      sid->u.ssl3.sessionID, sid->u.ssl3.sessionIDLength));

	sid->u.ssl3.lock = PR_NewRWLock(PR_RWLOCK_RANK_NONE, NULL);
	if (!sid->u.ssl3.lock) {
	    return;
	}
    }
    PORT_Assert(sid->creationTime != 0 && sid->expirationTime != 0);
    if (!sid->creationTime)
	sid->lastAccessTime = sid->creationTime = ssl_Time();
    if (!sid->expirationTime)
	sid->expirationTime = sid->creationTime + expirationPeriod;


    LOCK_CACHE;
    sid->references++;
    sid->cached = in_client_cache;
    sid->next   = cache;
    cache       = sid;
    UNLOCK_CACHE;
}
