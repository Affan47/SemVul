stan_GetCERTCertificate(NSSCertificate *c, PRBool forceUpdate)
{
    nssDecodedCert *dc = NULL;
    CERTCertificate *cc = NULL;
    CERTCertTrust certTrust;

    nssPKIObject_Lock(&c->object);

    dc = c->decoding;
    if (!dc) {
	dc = nssDecodedPKIXCertificate_Create(NULL, &c->encoding);
	if (!dc) {
            goto loser;
        }
	cc = (CERTCertificate *)dc->data;
	PORT_Assert(cc);
	if (!cc) {
	    nssDecodedPKIXCertificate_Destroy(dc);
	    nss_SetError(NSS_ERROR_INTERNAL_ERROR);
	    goto loser;
	}
    	PORT_Assert(!c->decoding);
	if (!c->decoding) {
	    c->decoding = dc;
	} else {

	    nssDecodedPKIXCertificate_Destroy(dc);
	    nss_SetError(NSS_ERROR_INTERNAL_ERROR);
            goto loser;
	}
    }
    cc = (CERTCertificate *)dc->data;
    PORT_Assert(cc);
    if (!cc) {
        nss_SetError(NSS_ERROR_INTERNAL_ERROR);
        goto loser;
    }
    if (!cc->nssCertificate || forceUpdate) {
        fill_CERTCertificateFields(c, cc, forceUpdate);
    } else if (CERT_GetCertTrust(cc, &certTrust) != SECSuccess &&
               !c->object.cryptoContext) {


        CERTCertTrust* trust = NULL;
        trust = nssTrust_GetCERTCertTrustForCert(c, cc);

        CERT_LockCertTrust(cc);
        cc->trust = trust;
        CERT_UnlockCertTrust(cc);
    }

  loser:
    nssPKIObject_Unlock(&c->object);
    return cc;
}
