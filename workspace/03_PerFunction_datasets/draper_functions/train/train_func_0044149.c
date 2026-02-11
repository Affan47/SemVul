ocsp_GetDecodedVerifiedSingleResponseForID(CERTCertDBHandle *handle,
					   CERTOCSPCertID *certID,
					   CERTCertificate *cert,
					   PRTime time,
					   void *pwArg,
					   const SECItem *encodedResponse,
					   CERTOCSPResponse **pDecodedResponse,
					   CERTOCSPSingleResponse **pSingle)
{
    CERTCertificate *signerCert = NULL;
    CERTCertificate *issuerCert = NULL;
    SECStatus rv = SECFailure;

    if (!pSingle || !pDecodedResponse) {
	return SECFailure;
    }
    *pSingle = NULL;
    *pDecodedResponse = CERT_DecodeOCSPResponse(encodedResponse);
    if (!*pDecodedResponse) {
	return SECFailure;
    }


    if (CERT_GetOCSPResponseStatus(*pDecodedResponse) != SECSuccess) {
	goto loser;
    }


    issuerCert = CERT_FindCertIssuer(cert, time, certUsageAnyCA);
    rv = CERT_VerifyOCSPResponseSignature(*pDecodedResponse, handle, pwArg,
                                          &signerCert, issuerCert);
    if (rv != SECSuccess) {
	goto loser;
    }

    PORT_Assert(signerCert != NULL);


    rv = ocsp_GetVerifiedSingleResponseForCertID(handle, *pDecodedResponse, certID,
                                                 signerCert, time, pSingle);
loser:
    if (issuerCert != NULL)
	CERT_DestroyCertificate(issuerCert);
    if (signerCert != NULL)
	CERT_DestroyCertificate(signerCert);
    return rv;
}
