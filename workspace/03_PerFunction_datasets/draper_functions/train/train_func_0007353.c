NSSCryptoContext_FindCertificatesByEmail (
  NSSCryptoContext *cc,
  NSSASCII7 *email,
  NSSCertificate *rvOpt[],
  PRUint32 maximumOpt,
  NSSArena *arenaOpt
)
{
    NSSCertificate **rvCerts;
    PORT_Assert(cc->certStore);
    if (!cc->certStore) {
	return NULL;
    }
    rvCerts = nssCertificateStore_FindCertificatesByEmail(cc->certStore,
                                                          email,
                                                          rvOpt,
                                                          maximumOpt,
                                                          arenaOpt);
    return rvCerts;
}
