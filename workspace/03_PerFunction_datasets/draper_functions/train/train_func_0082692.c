httpMakePath(HttpRoute *route, cchar *file)
{
    char    *path;

    mprAssert(route);
    mprAssert(file);

    if ((path = stemplate(file, route->pathTokens)) == 0) {
        return 0;
    }
    if (mprIsPathRel(path) && route->host) {
        path = mprJoinPath(route->host->home, path);
    }
    return mprGetAbsPath(path);
}
