manageHost(HttpHost *host, int flags)
{
    if (flags & MPR_MANAGE_MARK) {
        mprMark(host->name);
        mprMark(host->ip);
        mprMark(host->parent);
        mprMark(host->responseCache);
        mprMark(host->routes);
        mprMark(host->defaultRoute);
        mprMark(host->protocol);
        mprMark(host->mutex);
        mprMark(host->home);

    } else if (flags & MPR_MANAGE_FREE) {

        httpRemoveHost(MPR->httpService, host);
    }
}
