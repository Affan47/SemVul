SSLContextCiphersInit(NsOpenSSLContext *sslcontext)
{
    if (SSL_CTX_set_cipher_list(sslcontext->sslctx, sslcontext->cipherSuite) == 0) {
        Ns_Log(Error, "%s (%s): '%s' error setting cipher suite to '%s'",
                MODULE, sslcontext->server, sslcontext->name, sslcontext->cipherSuite);
        return NS_ERROR;
    }
    Ns_Log(Notice, "%s (%s): '%s' ciphers loaded successfully",
            MODULE, sslcontext->server, sslcontext->name);

    return NS_OK;
}
