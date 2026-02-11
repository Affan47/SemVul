CERT_EnableOCSPDefaultResponder(CERTCertDBHandle *handle)
{
    ocspCheckingContext *statusContext;
    CERTCertificate *cert;
    SECStatus rv;
    SECCertificateUsage usage;

    if (handle == NULL) {
	PORT_SetError(SEC_ERROR_INVALID_ARGS);
	return SECFailure;
    }

    statusContext = ocsp_GetCheckingContext(handle);

    if (statusContext == NULL) {


	PORT_SetError(SEC_ERROR_OCSP_NO_DEFAULT_RESPONDER);
	return SECFailure;
    }

    if (statusContext->defaultResponderURI == NULL) {
	PORT_SetError(SEC_ERROR_OCSP_NO_DEFAULT_RESPONDER);
	return SECFailure;
    }

    if (statusContext->defaultResponderNickname == NULL) {
	PORT_SetError(SEC_ERROR_OCSP_NO_DEFAULT_RESPONDER);
	return SECFailure;
    }


    cert = CERT_FindCertByNickname(handle,
				   statusContext->defaultResponderNickname);
    if (cert == NULL) {
        cert = PK11_FindCertFromNickname(statusContext->defaultResponderNickname,
                                         NULL);
    }


    PORT_Assert(cert != NULL);
    if (cert == NULL)
	return SECFailure;


    rv = CERT_VerifyCertificateNow(handle, cert, PR_TRUE,
                                   certificateUsageCheckAllUsages,
                                   NULL, &usage);
    if (rv != SECSuccess || (usage & (certificateUsageSSLClient |
                                      certificateUsageSSLServer |
                                      certificateUsageSSLServerWithStepUp |
                                      certificateUsageEmailSigner |
                                      certificateUsageObjectSigner |
                                      certificateUsageStatusResponder |
                                      certificateUsageSSLCA)) == 0) {
	PORT_SetError(SEC_ERROR_OCSP_RESPONDER_CERT_INVALID);
	return SECFailure;
    }


    statusContext->defaultResponderCert = cert;


    CERT_ClearOCSPCache();


    statusContext->useDefaultResponder = PR_TRUE;
    return SECSuccess;
}
