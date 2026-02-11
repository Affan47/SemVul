PK11_FindPrivateKeyFromCert(PK11SlotInfo *slot, CERTCertificate *cert,
								 void *wincx)
{
    int err;
    CK_OBJECT_CLASS certClass = CKO_CERTIFICATE;
    CK_ATTRIBUTE theTemplate[] = {
	{ CKA_VALUE, NULL, 0 },
	{ CKA_CLASS, NULL, 0 }
    };

    int tsize = sizeof(theTemplate)/sizeof(theTemplate[0]);
    CK_OBJECT_HANDLE certh;
    CK_OBJECT_HANDLE keyh;
    CK_ATTRIBUTE *attrs = theTemplate;
    PRBool needLogin;
    SECStatus rv;

    PK11_SETATTRS(attrs, CKA_VALUE, cert->derCert.data,
						cert->derCert.len); attrs++;
    PK11_SETATTRS(attrs, CKA_CLASS, &certClass, sizeof(certClass));


    rv = pk11_AuthenticateUnfriendly(slot, PR_TRUE, wincx);
    if (rv != SECSuccess) {
	return NULL;
    }

    certh = pk11_getcerthandle(slot,cert,theTemplate,tsize);
    if (certh == CK_INVALID_HANDLE) {
	return NULL;
    }


    needLogin = pk11_LoginStillRequired(slot,wincx);
    keyh = PK11_MatchItem(slot,certh,CKO_PRIVATE_KEY);
    if ((keyh == CK_INVALID_HANDLE) && needLogin &&
                        (SSL_ERROR_NO_CERTIFICATE == (err = PORT_GetError()) ||
			 SEC_ERROR_TOKEN_NOT_LOGGED_IN == err )) {

	rv = PK11_Authenticate(slot, PR_TRUE, wincx);
	if (rv != SECSuccess) {
	    return NULL;
	}
	keyh = PK11_MatchItem(slot,certh,CKO_PRIVATE_KEY);
    }
    if (keyh == CK_INVALID_HANDLE) {
	return NULL;
    }
    return PK11_MakePrivKey(slot, nullKey, PR_TRUE, keyh, wincx);
}
