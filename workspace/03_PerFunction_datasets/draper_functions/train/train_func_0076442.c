ssl_ResetSecurityInfo(sslSecurityInfo *sec, PRBool doMemset)
{

    if (sec->hash && sec->hashcx) {
	(*sec->hash->destroy)(sec->hashcx, PR_TRUE);
	sec->hashcx = NULL;
	sec->hash = NULL;
    }
    SECITEM_ZfreeItem(&sec->sendSecret, PR_FALSE);
    SECITEM_ZfreeItem(&sec->rcvSecret, PR_FALSE);


    if (sec->destroy) {
	(*sec->destroy)(sec->readcx, PR_TRUE);
	(*sec->destroy)(sec->writecx, PR_TRUE);
	sec->readcx = NULL;
	sec->writecx = NULL;
    } else {
	PORT_Assert(sec->readcx == 0);
	PORT_Assert(sec->writecx == 0);
    }
    sec->readcx = 0;
    sec->writecx = 0;

    if (sec->localCert) {
	CERT_DestroyCertificate(sec->localCert);
	sec->localCert = NULL;
    }
    if (sec->peerCert) {
	CERT_DestroyCertificate(sec->peerCert);
	sec->peerCert = NULL;
    }
    if (sec->peerKey) {
	SECKEY_DestroyPublicKey(sec->peerKey);
	sec->peerKey = NULL;
    }


    if (sec->ci.sid != NULL) {
	ssl_FreeSID(sec->ci.sid);
    }
    PORT_ZFree(sec->ci.sendBuf.buf, sec->ci.sendBuf.space);
    if (doMemset) {
        memset(&sec->ci, 0, sizeof sec->ci);
    }

}
