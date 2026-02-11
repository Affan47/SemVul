nssTrust_GetCERTCertTrustForCert(NSSCertificate *c, CERTCertificate *cc)
{
    CERTCertTrust *rvTrust = NULL;
    NSSTrustDomain *td = STAN_GetDefaultTrustDomain();
    NSSTrust *t;
    t = nssTrustDomain_FindTrustForCertificate(td, c);
    if (t) {
	rvTrust = cert_trust_from_stan_trust(t, cc->arena);
	if (!rvTrust) {
	    nssTrust_Destroy(t);
	    return NULL;
	}
	nssTrust_Destroy(t);
    } else {
	rvTrust = PORT_ArenaAlloc(cc->arena, sizeof(CERTCertTrust));
	if (!rvTrust) {
	    return NULL;
	}
	memset(rvTrust, 0, sizeof(*rvTrust));
    }
    if (NSSCertificate_IsPrivateKeyAvailable(c, NULL, NULL)) {
	rvTrust->sslFlags |= CERTDB_USER;
	rvTrust->emailFlags |= CERTDB_USER;
	rvTrust->objectSigningFlags |= CERTDB_USER;
    }
    return rvTrust;
}
