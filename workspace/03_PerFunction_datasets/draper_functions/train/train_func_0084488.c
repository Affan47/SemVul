DeleteCert(CERTCertDBHandle *handle, char *name)
{
    SECStatus rv;
    CERTCertificate *cert;

    cert = CERT_FindCertByNicknameOrEmailAddr(handle, name);
    if (!cert) {
	SECU_PrintError(progName, "could not find certificate named \"%s\"",
			name);
	return SECFailure;
    }

    rv = SEC_DeletePermCertificate(cert);
    CERT_DestroyCertificate(cert);
    if (rv) {
	SECU_PrintError(progName, "unable to delete certificate");
    }
    return rv;
}
