CMMF_DestroyCertRepContent(CMMFCertRepContent *inCertRepContent)
{
    PORT_Assert(inCertRepContent != NULL);
    if (inCertRepContent != NULL) {
        CMMFCertResponse   **pResponse = inCertRepContent->response;
        if (pResponse != NULL) {
            for (; *pResponse != NULL; pResponse++) {
	        CMMFCertifiedKeyPair *certKeyPair = (*pResponse)->certifiedKeyPair;


                if (certKeyPair != NULL                    &&
                    certKeyPair->certOrEncCert.choice == cmmfCertificate &&
                    certKeyPair->certOrEncCert.cert.certificate != NULL) {
                    CERT_DestroyCertificate
                                 (certKeyPair->certOrEncCert.cert.certificate);
		    certKeyPair->certOrEncCert.cert.certificate = NULL;
                }
            }
        }
	if (inCertRepContent->caPubs) {
	    CERTCertificate     **caPubs = inCertRepContent->caPubs;
	    for (; *caPubs; ++caPubs) {
		CERT_DestroyCertificate(*caPubs);
		*caPubs = NULL;
	    }
	}
	if (inCertRepContent->poolp != NULL) {
	    PORT_FreeArena(inCertRepContent->poolp, PR_TRUE);
	}
    }
    return SECSuccess;
}
