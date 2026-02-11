httpLookupEndpoint(Http *http, cchar *ip, int port)
{
    HttpEndpoint    *endpoint;
    int             next;

    if (ip == 0) {
        ip = "";
    }
    for (next = 0; (endpoint = mprGetNextItem(http->endpoints, &next)) != 0; ) {
        if (endpoint->port <= 0 || port <= 0 || endpoint->port == port) {
            mprAssert(endpoint->ip);
            if (*endpoint->ip == '\0' || *ip == '\0' || scmp(endpoint->ip, ip) == 0) {
                return endpoint;
            }
        }
    }
    return 0;
}
