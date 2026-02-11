SSLContextCADirInit(NsOpenSSLContext *sslcontext)
{
    DIR *dirfp = NULL;

    if (sslcontext->caDir == NULL ||
            SSL_CTX_load_verify_locations(sslcontext->sslctx, NULL, sslcontext->caDir) == 0) {
        Ns_Log(Warning, "%s (%s): '%s' error using CA directory '%s'",
                MODULE, sslcontext->server, sslcontext->name, sslcontext->caDir);
        dirfp = opendir(sslcontext->caDir);
        if (dirfp == NULL) {
            Ns_Log(Warning, "%s (%s): '%s' cannot open CA certificate directory",
                    MODULE, sslcontext->server, sslcontext->name);
        }
        closedir(dirfp);
    }
}
