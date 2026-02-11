ssl_NewSocket(PRBool makeLocks, SSLProtocolVariant protocolVariant)
{
    sslSocket *ss;

    ssl_SetDefaultsFromEnvironment();

    if (ssl_force_locks)
        makeLocks = PR_TRUE;


    ss = (sslSocket*) PORT_ZAlloc(sizeof(sslSocket));
    if (ss) {


        int i;
        SECStatus status;

        ss->opt                = ssl_defaults;
        ss->opt.useSocks       = PR_FALSE;
        ss->opt.noLocks        = !makeLocks;
        ss->vrange             = *VERSIONS_DEFAULTS(protocolVariant);
        ss->protocolVariant    = protocolVariant;

        ss->peerID             = NULL;
        ss->rTimeout           = PR_INTERVAL_NO_TIMEOUT;
        ss->wTimeout           = PR_INTERVAL_NO_TIMEOUT;
        ss->cTimeout           = PR_INTERVAL_NO_TIMEOUT;
        ss->cipherSpecs        = NULL;
        ss->sizeCipherSpecs    = 0;
        ss->preferredCipher    = NULL;
        ss->url                = NULL;

        for (i=kt_null; i < kt_kea_size; i++) {
            sslServerCerts * sc = ss->serverCerts + i;
            sc->serverCert      = NULL;
            sc->serverCertChain = NULL;
            sc->serverKeyPair   = NULL;
            sc->serverKeyBits   = 0;
            ss->certStatusArray[i] = NULL;
        }
        ss->stepDownKeyPair    = NULL;
        ss->dbHandle           = CERT_GetDefaultCertDB();


        ss->authCertificate    = SSL_AuthCertificate;
        ss->authCertificateArg = (void *)ss->dbHandle;
        ss->sniSocketConfig    = NULL;
        ss->sniSocketConfigArg = NULL;
        ss->getClientAuthData  = NULL;
        ss->handleBadCert      = NULL;
        ss->badCertArg         = NULL;
        ss->pkcs11PinArg       = NULL;
        ss->ephemeralECDHKeyPair = NULL;

        ssl_ChooseOps(ss);
        ssl2_InitSocketPolicy(ss);
        ssl3_InitSocketPolicy(ss);
        PR_INIT_CLIST(&ss->ssl3.hs.lastMessageFlight);

        if (makeLocks) {
            status = ssl_MakeLocks(ss);
            if (status != SECSuccess)
                goto loser;
        }
        status = ssl_CreateSecurityInfo(ss);
        if (status != SECSuccess)
            goto loser;
        status = ssl_InitGather(&ss->gs);
        if (status != SECSuccess) {
loser:
            ssl_DestroySocketContents(ss);
            ssl_DestroyLocks(ss);
            PORT_Free(ss);
            ss = NULL;
        }
    }
    return ss;
}
