NsOpenSSLContextRoleGet(char *server, NsOpenSSLContext *sslcontext)
{
    Ns_MutexLock(&sslcontext->lock);
    if (sslcontext->role == 0) {
        return "client";
    } else if (sslcontext->role == 1) {
        return "server";
    } else {
        return "undefined";
    }
    Ns_MutexUnlock(&sslcontext->lock);

    return NS_OK;
}
