httpSetRoutePrefix(HttpRoute *route, cchar *prefix)
{
    mprAssert(route);
    mprAssert(prefix && *prefix);

    route->prefix = sclone(prefix);
    route->prefixLen = slen(prefix);
    if (route->pattern) {
        finalizePattern(route);
    }
}
