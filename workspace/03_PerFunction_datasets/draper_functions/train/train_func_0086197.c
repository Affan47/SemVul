sec_pkcs7_add_recipient (SEC_PKCS7ContentInfo *cinfo,
			 CERTCertificate *cert,
			 SECCertUsage certusage,
			 CERTCertDBHandle *certdb)
{
    SECOidTag kind;
    SEC_PKCS7RecipientInfo *recipientinfo, **recipientinfos, ***recipientinfosp;
    SECItem *dummy;
    void *mark;
    int count;

    kind = SEC_PKCS7ContentType (cinfo);
    switch (kind) {
      case SEC_OID_PKCS7_ENVELOPED_DATA:
	{
	    SEC_PKCS7EnvelopedData *edp;

	    edp = cinfo->content.envelopedData;
	    recipientinfosp = &(edp->recipientInfos);
	}
	break;
      case SEC_OID_PKCS7_SIGNED_ENVELOPED_DATA:
	{
	    SEC_PKCS7SignedAndEnvelopedData *saedp;

	    saedp = cinfo->content.signedAndEnvelopedData;
	    recipientinfosp = &(saedp->recipientInfos);
	}
	break;
      default:
	return SECFailure;
    }


    if (certdb == NULL) {
	certdb = CERT_GetDefaultCertDB();
	if (certdb == NULL)
	    return SECFailure;
    }

    if (CERT_VerifyCert (certdb, cert, PR_TRUE, certusage, PR_Now(),
			 cinfo->pwfn_arg, NULL) != SECSuccess)
	{

	return SECFailure;
    }

    mark = PORT_ArenaMark (cinfo->poolp);

    recipientinfo = (SEC_PKCS7RecipientInfo*)PORT_ArenaZAlloc (cinfo->poolp,
				      sizeof(SEC_PKCS7RecipientInfo));
    if (recipientinfo == NULL) {
	PORT_ArenaRelease (cinfo->poolp, mark);
	return SECFailure;
    }

    dummy = SEC_ASN1EncodeInteger (cinfo->poolp, &recipientinfo->version,
				   SEC_PKCS7_RECIPIENT_INFO_VERSION);
    if (dummy == NULL) {
	PORT_ArenaRelease (cinfo->poolp, mark);
	return SECFailure;
    }
    PORT_Assert (dummy == &recipientinfo->version);

    recipientinfo->cert = CERT_DupCertificate (cert);
    if (recipientinfo->cert == NULL) {
	PORT_ArenaRelease (cinfo->poolp, mark);
	return SECFailure;
    }

    recipientinfo->issuerAndSN = CERT_GetCertIssuerAndSN (cinfo->poolp, cert);
    if (recipientinfo->issuerAndSN == NULL) {
	PORT_ArenaRelease (cinfo->poolp, mark);
	return SECFailure;
    }


    recipientinfos = *recipientinfosp;
    if (recipientinfos == NULL) {
	count = 0;
	recipientinfos = (SEC_PKCS7RecipientInfo **)PORT_ArenaAlloc (
					  cinfo->poolp,
					  2 * sizeof(SEC_PKCS7RecipientInfo *));
    } else {
	for (count = 0; recipientinfos[count] != NULL; count++)
	    ;
	PORT_Assert (count);
	recipientinfos = (SEC_PKCS7RecipientInfo **)PORT_ArenaGrow (
				 cinfo->poolp, recipientinfos,
				(count + 1) * sizeof(SEC_PKCS7RecipientInfo *),
				(count + 2) * sizeof(SEC_PKCS7RecipientInfo *));
    }

    if (recipientinfos == NULL) {
	PORT_ArenaRelease (cinfo->poolp, mark);
	return SECFailure;
    }

    recipientinfos[count] = recipientinfo;
    recipientinfos[count + 1] = NULL;

    *recipientinfosp = recipientinfos;

    PORT_ArenaUnmark (cinfo->poolp, mark);
    return SECSuccess;
}
