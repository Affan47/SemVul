NsSock_ModInit(char *server, char *module)
{
    Ns_DriverInitData init;
    char *path;
    int async;

    path = Ns_ConfigGetPath(server, module, NULL);
    if (!Ns_ConfigGetBool(path, "async", &async)) {
	async = 1;
    }


    init.version = NS_DRIVER_VERSION_1;
    init.name = "nssock";
    init.proc = SockProc;
    init.opts = (async ? NS_DRIVER_ASYNC : 0);
    init.arg = NULL;
    init.path = NULL;

    return Ns_DriverInit(server, module, &init);
}
