find_cert_issuer (
  NSSCertificate *c,
  NSSTime *timeOpt,
  NSSUsage *usage,
  NSSPolicies *policiesOpt,
  NSSTrustDomain *td,
  NSSCryptoContext *cc
)
{
    NSSArena *arena;
    NSSCertificate **certs = NULL;
    NSSCertificate **ccIssuers = NULL;
    NSSCertificate **tdIssuers = NULL;
    NSSCertificate *issuer = NULL;

    if (!cc)
	cc = c->object.cryptoContext;
    if (!td)
	td = NSSCertificate_GetTrustDomain(c);
    arena = nssArena_Create();
    if (!arena) {
	return (NSSCertificate *)NULL;
    }
    if (cc) {
	ccIssuers = nssCryptoContext_FindCertificatesBySubject(cc,
	                                                       &c->issuer,
	                                                       NULL,
	                                                       0,
	                                                       arena);
    }
    if (td)
	tdIssuers = nssTrustDomain_FindCertificatesBySubject(td,
                                                         &c->issuer,
                                                         NULL,
                                                         0,
                                                         arena);
    certs = nssCertificateArray_Join(ccIssuers, tdIssuers);
    if (certs) {
	nssDecodedCert *dc = NULL;
	void *issuerID = NULL;
	dc = nssCertificate_GetDecoding(c);
	if (dc) {
	    issuerID = dc->getIssuerIdentifier(dc);
	}


	if (issuerID) {
	    certs = filter_subject_certs_for_id(certs, issuerID);
	}
	certs = filter_certs_for_valid_issuers(certs);
	issuer = nssCertificateArray_FindBestCertificate(certs,
	                                                 timeOpt,
	                                                 usage,
	                                                 policiesOpt);
	nssCertificateArray_Destroy(certs);
    }
    nssArena_Destroy(arena);
    return issuer;
}
