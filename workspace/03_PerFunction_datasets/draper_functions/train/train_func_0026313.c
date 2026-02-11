sec_pkcs12_find_cert_in_certbag(SEC_PKCS12CertAndCRLBag *certbag,
				SECItem *nickname, SGNDigestInfo *thumbprint)
{
    PRBool search_both = PR_FALSE, search_nickname = PR_FALSE;
    int i, j;

    if((certbag == NULL) || ((nickname == NULL) && (thumbprint == NULL))) {
	return NULL;
    }

    if(thumbprint && nickname) {
	search_both = PR_TRUE;
    }

    if(nickname) {
	search_nickname = PR_TRUE;
    }

search_again:
    i = 0;
    while(certbag->certAndCRLs[i] != NULL) {
	SEC_PKCS12CertAndCRL *cert = certbag->certAndCRLs[i];

	if(SECOID_FindOIDTag(&cert->BagID) == SEC_OID_PKCS12_X509_CERT_CRL_BAG) {


	    if(search_nickname) {
		if(SECITEM_CompareItem(nickname, &cert->nickname) == SECEqual) {
		    return cert;
		}
	    } else {

		SECItem **derCertList;


		derCertList = SEC_PKCS7GetCertificateList(&cert->value.x509->certOrCRL);
		j = 0;
		if(derCertList != NULL) {
		    while(derCertList[j] != NULL) {
			SECComparison eq;
			SGNDigestInfo *di;
			di = sec_pkcs12_compute_thumbprint(derCertList[j]);
			if(di) {
			    eq = SGN_CompareDigestInfo(thumbprint, di);
			    SGN_DestroyDigestInfo(di);
			    if(eq == SECEqual) {

				cert->value.x509->derLeafCert = derCertList[j];
				return cert;
			    }
			} else {

			    return NULL;
			}
			j++;
		    }
		}
	    }
	}

	i++;
    }

    if(search_both) {
	search_both = PR_FALSE;
	search_nickname = PR_FALSE;
	goto search_again;
    }

    return NULL;
}
