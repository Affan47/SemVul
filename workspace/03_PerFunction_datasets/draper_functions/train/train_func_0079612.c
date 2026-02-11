SECU_FindCrlIssuer(CERTCertDBHandle *dbhandle, SECItem* subject,
                   CERTAuthKeyID* authorityKeyID, PRTime validTime)
{
    CERTCertificate *issuerCert = NULL;
    CERTCertList *certList = NULL;
    CERTCertTrust trust;

    if (!subject) {
        PORT_SetError(SEC_ERROR_INVALID_ARGS);
        return NULL;
    }

    certList =
        CERT_CreateSubjectCertList(NULL, dbhandle, subject,
                                   validTime, PR_TRUE);
    if (certList) {
        CERTCertListNode *node = CERT_LIST_HEAD(certList);


        while ( ! CERT_LIST_END(node, certList) ) {
            CERTCertificate *cert = node->cert;


            if (CERT_GetCertTrust(cert, &trust) == SECSuccess &&
                CERT_CheckCertUsage(cert, KU_CRL_SIGN) == SECSuccess &&
                CERT_IsUserCert(cert)) {

                issuerCert = CERT_DupCertificate(cert);
                break;
            }
            node = CERT_LIST_NEXT(node);
        }
        CERT_DestroyCertList(certList);
    }
    return(issuerCert);
}
