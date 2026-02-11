maSslModuleInit(Http *http, MprModule *module)
{
    HttpStage   *stage;
    MaAppweb    *appweb;

    if (mprLoadSsl(1) == 0) {
        return MPR_ERR_CANT_CREATE;
    }
    if ((stage = httpCreateStage(http, "sslModule", HTTP_STAGE_MODULE, module)) == 0) {
        return MPR_ERR_CANT_CREATE;
    }
    appweb = httpGetContext(http);
    maAddDirective(appweb, "SSL", sslDirective);
    maAddDirective(appweb, "SSLEngine", sslDirective);
#if FUTURE && MOB
    maAddDirective(appweb, "ListenSecure", listenSecureDirective);
#endif
    maAddDirective(appweb, "SSLCACertificateFile", sslCaCertificateFileDirective);
    maAddDirective(appweb, "SSLCACertificatePath", sslCaCertificatePathDirective);
    maAddDirective(appweb, "SSLCertificateFile", sslCertificateFileDirective);
    maAddDirective(appweb, "SSLCertificateKeyFile", sslCertificateKeyFileDirective);
    maAddDirective(appweb, "SSLCipherSuite", sslCipherSuiteDirective);
    maAddDirective(appweb, "SSLProtocol", sslProtocolDirective);
    maAddDirective(appweb, "SSLVerifyClient", sslVerifyClientDirective);
    return 0;
}
