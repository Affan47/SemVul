NSS_SMIMEUtil_GetCertFromEncryptionKeyPreference(CERTCertDBHandle *certdb, SECItem *DERekp)
{
    PLArenaPool *tmppoolp = NULL;
    CERTCertificate *cert = NULL;
    NSSSMIMEEncryptionKeyPreference ekp;

    tmppoolp = PORT_NewArena(1024);
    if (tmppoolp == NULL)
	return NULL;


    if (SEC_QuickDERDecodeItem(tmppoolp, &ekp, smime_encryptionkeypref_template,
                               DERekp) != SECSuccess)
	goto loser;


    switch (ekp.selector) {
    case NSSSMIMEEncryptionKeyPref_IssuerSN:
	cert = CERT_FindCertByIssuerAndSN(certdb, ekp.id.issuerAndSN);
	break;
    case NSSSMIMEEncryptionKeyPref_RKeyID:
    case NSSSMIMEEncryptionKeyPref_SubjectKeyID:

	break;
    default:
	PORT_Assert(0);
    }
loser:
    if (tmppoolp) PORT_FreeArena(tmppoolp, PR_FALSE);

    return cert;
}
