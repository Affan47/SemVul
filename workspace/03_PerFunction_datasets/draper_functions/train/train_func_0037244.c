ocsp_matchcert(SECItem *certIndex,CERTCertificate *testCert)
{
    SECItem item;
    unsigned char buf[HASH_LENGTH_MAX];

    item.data = buf;
    item.len = SHA1_LENGTH;

    if (CERT_GetSubjectPublicKeyDigest(NULL,testCert,SEC_OID_SHA1,
				       &item) == NULL) {
	return PR_FALSE;
    }
    if  (SECITEM_ItemsAreEqual(certIndex,&item)) {
	return PR_TRUE;
    }
    if (CERT_GetSubjectPublicKeyDigest(NULL,testCert,SEC_OID_MD5,
				       &item) == NULL) {
	return PR_FALSE;
    }
    if  (SECITEM_ItemsAreEqual(certIndex,&item)) {
	return PR_TRUE;
    }
    if (CERT_GetSubjectPublicKeyDigest(NULL,testCert,SEC_OID_MD2,
				       &item) == NULL) {
	return PR_FALSE;
    }
    if  (SECITEM_ItemsAreEqual(certIndex,&item)) {
	return PR_TRUE;
    }

    return PR_FALSE;
}
