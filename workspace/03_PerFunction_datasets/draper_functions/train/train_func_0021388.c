PK11_ImportDERCertForKey(SECItem *derCert, char *nickname,void *wincx)
{
    CERTCertificate *cert;
    PK11SlotInfo *slot = NULL;

    cert = CERT_NewTempCertificate(CERT_GetDefaultCertDB(),
                                   derCert, NULL, PR_FALSE, PR_TRUE);
    if (cert == NULL) return NULL;

    slot = PK11_ImportCertForKey(cert, nickname, wincx);
    CERT_DestroyCertificate (cert);
    return slot;
}
