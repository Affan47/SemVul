CERT_CertChainFromCert(CERTCertificate *cert, SECCertUsage usage,
		       PRBool includeRoot)
{
    CERTCertificateList *chain = NULL;
    NSSCertificate **stanChain;
    NSSCertificate *stanCert;
    PLArenaPool *arena;
    NSSUsage nssUsage;
    int i, len;
    NSSTrustDomain *td   = STAN_GetDefaultTrustDomain();
    NSSCryptoContext *cc = STAN_GetDefaultCryptoContext();

    stanCert = STAN_GetNSSCertificate(cert);
    if (!stanCert) {

        return NULL;
    }
    nssUsage.anyUsage = PR_FALSE;
    nssUsage.nss3usage = usage;
    nssUsage.nss3lookingForCA = PR_FALSE;
    stanChain = NSSCertificate_BuildChain(stanCert, NULL, &nssUsage, NULL, NULL,
					  CERT_MAX_CERT_CHAIN, NULL, NULL, td, cc);
    if (!stanChain) {
	PORT_SetError(SEC_ERROR_UNKNOWN_ISSUER);
	return NULL;
    }

    len = 0;
    stanCert = stanChain[0];
    while (stanCert) {
	stanCert = stanChain[++len];
    }

    arena = PORT_NewArena(4096);
    if (arena == NULL) {
	goto loser;
    }

    chain = (CERTCertificateList *)PORT_ArenaAlloc(arena,
                                                 sizeof(CERTCertificateList));
    if (!chain) goto loser;
    chain->certs = (SECItem*)PORT_ArenaAlloc(arena, len * sizeof(SECItem));
    if (!chain->certs) goto loser;
    i = 0;
    stanCert = stanChain[i];
    while (stanCert) {
	SECItem derCert;
	CERTCertificate *cCert = STAN_GetCERTCertificate(stanCert);
	if (!cCert) {
	    goto loser;
	}
	derCert.len = (unsigned int)stanCert->encoding.size;
	derCert.data = (unsigned char *)stanCert->encoding.data;
	derCert.type = siBuffer;
	SECITEM_CopyItem(arena, &chain->certs[i], &derCert);
	stanCert = stanChain[++i];
	if (!stanCert && !cCert->isRoot) {


	    includeRoot = PR_TRUE;
	}
	CERT_DestroyCertificate(cCert);
    }
    if ( !includeRoot && len > 1) {
	chain->len = len - 1;
    } else {
	chain->len = len;
    }

    chain->arena = arena;
    nss_ZFreeIf(stanChain);
    return chain;
loser:
    i = 0;
    stanCert = stanChain[i];
    while (stanCert) {
	CERTCertificate *cCert = STAN_GetCERTCertificate(stanCert);
	if (cCert) {
	    CERT_DestroyCertificate(cCert);
	}
	stanCert = stanChain[++i];
    }
    nss_ZFreeIf(stanChain);
    if (arena) {
	PORT_FreeArena(arena, PR_FALSE);
    }
    return NULL;
}
