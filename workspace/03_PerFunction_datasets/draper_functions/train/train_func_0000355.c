ssl_ConfigSecureServer(sslSocket *ss, CERTCertificate *cert,
                       const CERTCertificateList *certChain,
                       ssl3KeyPair *keyPair, SSLKEAType kea)
{
    CERTCertificateList *localCertChain = NULL;
    sslServerCerts  *sc = ss->serverCerts + kea;


    if (sc->serverCert != NULL) {
	CERT_DestroyCertificate(sc->serverCert);
    	sc->serverCert = NULL;
        sc->serverKeyBits = 0;
    }

    if (sc->serverCertChain != NULL) {
	CERT_DestroyCertificateList(sc->serverCertChain);
    	sc->serverCertChain = NULL;
    }
    if (cert) {
        sc->serverCert = CERT_DupCertificate(cert);

        sc->serverKeyBits = SECKEY_PublicKeyStrengthInBits(keyPair->pubKey);
        if (!certChain) {
            localCertChain =
                CERT_CertChainFromCert(sc->serverCert, certUsageSSLServer,
                                       PR_TRUE);
            if (!localCertChain)
                goto loser;
        }
        sc->serverCertChain = (certChain) ? CERT_DupCertList(certChain) :
                                            localCertChain;
        if (!sc->serverCertChain) {
            goto loser;
        }
        localCertChain = NULL;
    }


    if (sc->serverKeyPair != NULL) {
        ssl3_FreeKeyPair(sc->serverKeyPair);
        sc->serverKeyPair = NULL;
    }
    if (keyPair) {
        SECKEY_CacheStaticFlags(keyPair->privKey);
        sc->serverKeyPair = ssl3_GetKeyPairRef(keyPair);
    }
    if (kea == kt_rsa && cert && sc->serverKeyBits > 512 &&
        !ss->opt.noStepDown && !ss->stepDownKeyPair) {
        if (ssl3_CreateRSAStepDownKeys(ss) != SECSuccess) {
            goto loser;
        }
    }
    return SECSuccess;

loser:
    if (localCertChain) {
        CERT_DestroyCertificateList(localCertChain);
    }
    if (sc->serverCert != NULL) {
	CERT_DestroyCertificate(sc->serverCert);
	sc->serverCert = NULL;
    }
    if (sc->serverCertChain != NULL) {
	CERT_DestroyCertificateList(sc->serverCertChain);
	sc->serverCertChain = NULL;
    }
    if (sc->serverKeyPair != NULL) {
	ssl3_FreeKeyPair(sc->serverKeyPair);
	sc->serverKeyPair = NULL;
    }
    return SECFailure;
}
