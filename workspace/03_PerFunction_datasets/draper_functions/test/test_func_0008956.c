httpStopEndpoint(HttpEndpoint *endpoint)
{
    HttpHost    *host;
    int         next;

    for (ITERATE_ITEMS(endpoint->hosts, host, next)) {
        httpStopHost(host);
    }
    if (endpoint->waitHandler) {
        mprRemoveWaitHandler(endpoint->waitHandler);
        endpoint->waitHandler = 0;
    }
    if (endpoint->sock) {
        mprRemoveSocketHandler(endpoint->sock);
        mprCloseSocket(endpoint->sock, 0);
        endpoint->sock = 0;
    }
}
