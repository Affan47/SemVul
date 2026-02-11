ocsp_CertIDsMatch(CERTOCSPCertID *requestCertID,
		  CERTOCSPCertID *responseCertID)
{
    PRBool match = PR_FALSE;
    SECOidTag hashAlg;
    SECItem *keyHash = NULL;
    SECItem *nameHash = NULL;


    if (SECITEM_CompareItem(&requestCertID->serialNumber,
			    &responseCertID->serialNumber) != SECEqual) {
	goto done;
    }


    if (responseCertID->hashAlgorithm.parameters.len > 2) {
	goto done;
    }
    if (SECITEM_CompareItem(&requestCertID->hashAlgorithm.algorithm,
		&responseCertID->hashAlgorithm.algorithm) == SECEqual) {


	if ((SECITEM_CompareItem(&requestCertID->issuerNameHash,
				&responseCertID->issuerNameHash) == SECEqual)
	    && (SECITEM_CompareItem(&requestCertID->issuerKeyHash,
				&responseCertID->issuerKeyHash) == SECEqual)) {
	    match = PR_TRUE;
	}
	goto done;
    }

    hashAlg = SECOID_FindOIDTag(&responseCertID->hashAlgorithm.algorithm);
    switch (hashAlg) {
    case SEC_OID_SHA1:
	keyHash = &requestCertID->issuerSHA1KeyHash;
	nameHash = &requestCertID->issuerSHA1NameHash;
	break;
    case SEC_OID_MD5:
	keyHash = &requestCertID->issuerMD5KeyHash;
	nameHash = &requestCertID->issuerMD5NameHash;
	break;
    case SEC_OID_MD2:
	keyHash = &requestCertID->issuerMD2KeyHash;
	nameHash = &requestCertID->issuerMD2NameHash;
	break;
    default:
	PORT_SetError(SEC_ERROR_INVALID_ALGORITHM);
 	return PR_FALSE;
    }

    if ((keyHash != NULL)
	&& (SECITEM_CompareItem(nameHash,
				&responseCertID->issuerNameHash) == SECEqual)
	&& (SECITEM_CompareItem(keyHash,
				&responseCertID->issuerKeyHash) == SECEqual)) {
	match = PR_TRUE;
    }

done:
    return match;
}
