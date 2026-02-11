definePathVars(HttpRoute *route)
{
    mprAssert(route);

    mprAddKey(route->pathTokens, "PRODUCT", sclone(BLD_PRODUCT));
    mprAddKey(route->pathTokens, "OS", sclone(BLD_OS));
    mprAddKey(route->pathTokens, "VERSION", sclone(BLD_VERSION));
    mprAddKey(route->pathTokens, "LIBDIR", mprJoinPath(mprGetPathParent(mprGetAppDir()), mprGetPathBase(BLD_LIB_NAME)));
    if (route->host) {
        defineHostVars(route);
    }
}
