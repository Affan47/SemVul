maCreateServer(MaAppweb *appweb, cchar *name)
{
    MaServer    *server;

    mprAssert(appweb);

    if ((server = mprAllocObj(MaServer, manageServer)) == NULL) {
        return 0;
    }
    if (name == 0 || *name == '\0') {
        name = "default";
    }
    server->name = sclone(name);
    server->endpoints = mprCreateList(-1, 0);
    server->limits = httpCreateLimits(1);
    server->appweb = appweb;
    server->http = appweb->http;
    maAddServer(appweb, server);
    if (appweb->defaultServer == 0) {
        maSetDefaultServer(appweb, server);
    }
    return server;
}
