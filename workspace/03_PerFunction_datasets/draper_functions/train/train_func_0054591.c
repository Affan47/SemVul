nssTrustDomain_GetCertByDERFromCache (
  NSSTrustDomain *td,
  NSSDER *der
)
{
    PRStatus nssrv = PR_FAILURE;
    NSSDER issuer, serial;
    NSSCertificate *rvCert;
    nssrv = issuer_and_serial_from_encoding(der, &issuer, &serial);
    if (nssrv != PR_SUCCESS) {
	return NULL;
    }
#ifdef DEBUG_CACHE
    log_item_dump("looking for cert by DER", der);
#endif
    rvCert = nssTrustDomain_GetCertForIssuerAndSNFromCache(td,
                                                           &issuer, &serial);
    PORT_Free(issuer.data);
    PORT_Free(serial.data);
    return rvCert;
}
