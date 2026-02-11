CMMF_CreateCertRepContentFromDER(CERTCertDBHandle *db, const char *buf,
				 long len)
{
    PLArenaPool        *poolp;
    CMMFCertRepContent *certRepContent;
    SECStatus           rv;
    int                 i;

    poolp = PORT_NewArena(CRMF_DEFAULT_ARENA_SIZE);
    if (poolp == NULL) {
        return NULL;
    }
    certRepContent = PORT_ArenaZNew(poolp, CMMFCertRepContent);
    if (certRepContent == NULL) {
        goto loser;
    }
    certRepContent->poolp = poolp;
    rv = SEC_ASN1Decode(poolp, certRepContent, CMMFCertRepContentTemplate,
			buf, len);
    if (rv != SECSuccess) {
        goto loser;
    }
    if (certRepContent->response != NULL) {
        for (i=0; certRepContent->response[i] != NULL; i++) {
	    rv = cmmf_decode_process_cert_response(poolp, db,
					       certRepContent->response[i]);
	    if (rv != SECSuccess) {
	        goto loser;
	    }
	}
    }
    certRepContent->isDecoded = PR_TRUE;
    return certRepContent;
 loser:
    PORT_FreeArena(poolp, PR_FALSE);
    return NULL;
}
