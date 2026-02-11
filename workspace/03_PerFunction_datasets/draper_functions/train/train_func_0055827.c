mhCleanup(MockHTTP *mh)
{
    if (!mh)
        return;

    if (mh->servCtx) {
        mhStopServer(mh->servCtx);
    }

    if (mh->proxyCtx) {
        mhStopServer(mh->proxyCtx);
    }


    apr_pool_destroy(mh->pool);


}
