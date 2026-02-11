ssl3_CipherPrefSet(sslSocket *ss, ssl3CipherSuite which, PRBool enabled)
{
    ssl3CipherSuiteCfg *suite;

    suite = ssl_LookupCipherSuiteCfg(which, ss->cipherSuites);
    if (suite == NULL) {
	return SECFailure;
    }
    suite->enabled = enabled;
    return SECSuccess;
}
