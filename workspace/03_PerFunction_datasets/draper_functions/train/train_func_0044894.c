httpSetRouteSource(HttpRoute *route, cchar *source)
{
    mprAssert(route);
    mprAssert(source);


    route->sourceName = sclone(source);
}
