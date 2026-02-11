httpAddRouteErrorDocument(HttpRoute *route, int status, cchar *url)
{
    char    *code;

    mprAssert(route);
    GRADUATE_HASH(route, errorDocuments);
    code = itos(status);
    mprAddKey(route->errorDocuments, code, sclone(url));
}
