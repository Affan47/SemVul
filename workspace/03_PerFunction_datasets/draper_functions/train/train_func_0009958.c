ocsp_GetVerifiedSingleResponseForCertID(CERTCertDBHandle *handle,
                                        CERTOCSPResponse *response,
                                        CERTOCSPCertID   *certID,
                                        CERTCertificate  *signerCert,
                                        PRTime            time,
                                        CERTOCSPSingleResponse
                                            **pSingleResponse)
{
    SECStatus rv;
    ocspResponseData *responseData;
    PRTime producedAt;
    CERTOCSPSingleResponse *single;


    responseData = ocsp_GetResponseData(response, NULL);
    if (responseData == NULL) {
        rv = SECFailure;
        goto loser;
    }


    rv = DER_GeneralizedTimeToTime(&producedAt, &responseData->producedAt);
    if (rv != SECSuccess)
        goto loser;

    single = ocsp_GetSingleResponseForCertID(responseData->responses,
                                             handle, certID);
    if (single == NULL) {
        rv = SECFailure;
        goto loser;
    }

    rv = ocsp_VerifySingleResponse(single, handle, signerCert, producedAt);
    if (rv != SECSuccess)
        goto loser;
    *pSingleResponse = single;

loser:
    return rv;
}
